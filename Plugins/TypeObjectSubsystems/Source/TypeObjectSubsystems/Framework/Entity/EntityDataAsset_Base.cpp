// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Entity/EntityDataAsset_Base.h"

#include "AssetRegistry/IAssetRegistry.h"
#include "GameplayTagsManager.h"
#include "UObject/ObjectKey.h"

#if WITH_EDITOR
#include "Containers/Ticker.h"
#include "GameplayTagRedirectors.h"
#include "GameplayTagsSettings.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFileManager.h"
#include "ISourceControlModule.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/DataValidation.h"
#include "Misc/Paths.h"
#include "SourceControlHelpers.h"
#include "UObject/ObjectSaveContext.h"
#include "UObject/UnrealType.h"
#endif

#include "AssertUtils/Assert.h"

#include "Framework/AssetManager/EnhancedAssetManager.h"
#include "Framework/Entity/EntitySubsystem_Base.h"

namespace UE::TypeObjectSubsystems::Private
{
	/** True if the key lies in the namespace: its name starts with the prefix ([DA tag ID].) and has something after it. */
	bool IsKeyInNamespace(const FGameplayTag& Key, const FString& AssetTagIDPrefix)
	{
		assertStringIsNotEmpty_return(AssetTagIDPrefix, false);

		const FString KeyString = Key.GetTagName().ToString();
		return KeyString.Len() > AssetTagIDPrefix.Len() && KeyString.StartsWith(AssetTagIDPrefix, ESearchCase::IgnoreCase);
	}

#if WITH_EDITOR
	/** Marker meta of a top-level TMap<FGameplayTag, *> property whose keys the base generates. */
	const FName GeneratedKeysMetaName = TEXT("UTOSGeneratedKeys");

	/** Returns the top-level map properties of the class marked UTOSGeneratedKeys; a marked map not keyed by FGameplayTag is reported and skipped. */
	TArray<const FMapProperty*> FindGeneratedKeysMaps(const UClass* Class)
	{
		assertUObjectPointerIsValid_return(Class, {});

		TArray<const FMapProperty*> Maps;
		for (TFieldIterator<FMapProperty> PropertyIterator(Class); PropertyIterator; ++PropertyIterator)
		{
			const FMapProperty* const MapProperty = *PropertyIterator;
			assertIsNotNull_withContinue(MapProperty);

			if (!MapProperty->HasMetaData(GeneratedKeysMetaName))
			{
				continue;
			}

			const FStructProperty* const KeyProperty = CastField<FStructProperty>(MapProperty->KeyProp);
			const bool bKeyedByTag = KeyProperty != nullptr && KeyProperty->Struct == FGameplayTag::StaticStruct();
			assertIsTrue_withContinue(bKeyedByTag);

			Maps.Add(MapProperty);
		}

		return Maps;
	}
#endif
}

using namespace UE::TypeObjectSubsystems::Private;

FPrimaryAssetId UEntityDataAsset_Base::GetPrimaryAssetId() const
{
	// a native class default object is a type, not an asset (same rule as UPrimaryDataAsset, DataAsset.cpp:80-84)
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return FPrimaryAssetId();
	}

	// the concrete native class name is the primary asset type — e.g. ItemDatabaseDataAsset
	return FPrimaryAssetId(GetClass()->GetFName(), GetFName());
}

void UEntityDataAsset_Base::PostRename(UObject* OldOuter, const FName OldName)
{
	Super::PostRename(OldOuter, OldName);

#if WITH_EDITOR
	assertNameIsAssigned_return(OldName);

	// only a real rename of an asset: not a CDO, not a delete (the object moves into the transient package and stops being an asset),
	// not a move to another folder that keeps the name; FName compares without case, so a case-only change keeps the tags too
	if (!GIsEditor || !IsAsset() || OldName == GetFName())
	{
		return;
	}

	const FGameplayTag RootTag = GetNativeTags().GetRootTag();
	assertGameplayTagIsValid_return(RootTag);

	const FName NewAssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(NewAssetTagIDName);

	const FString OldAssetTagIDString = RootTag.ToString() + TEXT(".") + OldName.ToString();

	TArray<TPair<FName, FName>> Redirects;
	Redirects.Emplace(FName(OldAssetTagIDString), NewAssetTagIDName);
	RebaseGeneratedKeys(OldAssetTagIDString, Redirects);

	RegisterAllIDsAsNativeGameplayTags();
	AddGameplayTagRedirects(Redirects);

	MarkPackageDirty();
#endif
}

void UEntityDataAsset_Base::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

#if WITH_EDITOR
	// a duplicated asset only; PIE and world duplicates keep the keys they were copied with
	if (DuplicateMode != EDuplicateMode::Normal || !GIsEditor || !IsAsset())
	{
		return;
	}

	// the copy still carries the source's keys; it keeps their indices and the copied counter, without redirects
	const FString SourceAssetTagIDString = FindForeignAssetTagIDOfKeys();
	if (!SourceAssetTagIDString.IsEmpty())
	{
		TArray<TPair<FName, FName>> RenamedTags;
		RebaseGeneratedKeys(SourceAssetTagIDString, RenamedTags);
	}

	RegisterAllIDsAsNativeGameplayTags();

	MarkPackageDirty();
#endif
}

#if WITH_EDITOR
void UEntityDataAsset_Base::PostLoad()
{
	Super::PostLoad();

	SavedIndexCounter = IndexCounter;
}

void UEntityDataAsset_Base::PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext)
{
	Super::PostSaveRoot(ObjectSaveContext);

	// only a user save into the asset's own file puts the counter on disk; cooks and autosaves do not
	if (ObjectSaveContext.SaveSucceeded() && !ObjectSaveContext.IsProceduralSave() && !ObjectSaveContext.IsFromAutoSave())
	{
		SavedIndexCounter = IndexCounter;
	}
}

void UEntityDataAsset_Base::PostEditUndo()
{
	Super::PostEditUndo();

	// the undo restores the package's dirty flag and refuses to re-dirty it while it runs (GIsTransacting, EditorTransaction.cpp
	// FTransaction::Apply); a counter that moved past the saved one must still reach the disk — dirty the package once the undo is over
	if (IndexCounter == SavedIndexCounter)
	{
		return;
	}

	const TWeakObjectPtr<UEntityDataAsset_Base> WeakThis{this};
	FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([WeakThis](float)
	{
		UEntityDataAsset_Base* const DataAsset = WeakThis.Get();
		if (DataAsset != nullptr)
		{
			DataAsset->MarkPackageDirty();
		}

		// one shot
		return false;
	}));
}

void UEntityDataAsset_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// the class default object is a type, it has no asset name to compose keys from
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	// an added element, a paste or a script write into a marked map all end here; no member property means an undo or a whole-object change
	const FProperty* const MemberProperty = PropertyChangedEvent.MemberProperty;
	const bool bMayTouchMarkedMap = MemberProperty == nullptr || MemberProperty->HasMetaData(GeneratedKeysMetaName);
	if (!bMayTouchMarkedMap)
	{
		return;
	}

	if (NormalizeGeneratedKeys())
	{
		MarkPackageDirty();
	}
}

EDataValidationResult UEntityDataAsset_Base::IsDataValid(FDataValidationContext& Context) const
{
	const EDataValidationResult SuperResult = Super::IsDataValid(Context);

	const FName AssetTagIDName = ComposeAssetTagIDName();
	if (AssetTagIDName.IsNone())
	{
		Context.AddError(FText::FromString(FString::Printf(TEXT("%s: the asset name does not form a valid DA tag ID"), *GetName())));
		return EDataValidationResult::Invalid;
	}

	const FString AssetTagIDPrefix = AssetTagIDName.ToString() + TEXT(".");

	bool bKeysValid = true;
	for (const FMapProperty* const MapProperty : FindGeneratedKeysMaps(GetClass()))
	{
		assertIsNotNull_withContinue(MapProperty);

		const FScriptMapHelper MapHelper(MapProperty, MapProperty->ContainerPtrToValuePtr<void>(this));
		for (FScriptMapHelper::FIterator MapIterator = MapHelper.CreateIterator(); MapIterator; ++MapIterator)
		{
			const FGameplayTag& Key = *reinterpret_cast<const FGameplayTag*>(MapHelper.GetKeyPtr(MapIterator));

			if (Key.GetTagName().IsNone())
			{
				Context.AddError(FText::FromString(FString::Printf(TEXT("%s: an element of %s has an empty key"),
				                                                   *GetName(), *MapProperty->GetName())));
				bKeysValid = false;
				continue;
			}

			if (!IsKeyInNamespace(Key, AssetTagIDPrefix))
			{
				Context.AddError(FText::FromString(FString::Printf(TEXT("%s: key %s of %s is outside the namespace %s"),
				                                                   *GetName(), *Key.ToString(), *MapProperty->GetName(), *AssetTagIDName.ToString())));
				bKeysValid = false;
			}
		}
	}

	return CombineDataValidationResults(SuperResult, bKeysValid ? EDataValidationResult::Valid : EDataValidationResult::Invalid);
}
#endif

FName UEntityDataAsset_Base::ComposeAssetTagIDName() const
{
	const FGameplayTag RootTag = GetNativeTags().GetRootTag();
	assertGameplayTagIsValid_return(RootTag, NAME_None);

	const FName AssetName = GetCategoryName();
	assertNameIsAssigned_return(AssetName, NAME_None);

	const FString AssetTagIDString = RootTag.ToString() + TEXT(".") + AssetName.ToString();

	const bool bValidTagString = UGameplayTagsManager::Get().IsValidGameplayTagString(AssetTagIDString);
	assertIsTrue_return(bValidTagString, NAME_None);

	return FName(AssetTagIDString);
}

void UEntityDataAsset_Base::RegisterKeysAsNativeGameplayTags(TConstArrayView<FGameplayTag> Keys) const
{
	const FName AssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(AssetTagIDName);

	const FString AssetTagIDPrefix = AssetTagIDName.ToString() + TEXT(".");
	const FString TagComment = FString::Printf(TEXT("(Native) Entity of DataAsset %s"), *GetPathName());

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	// one tree-changed broadcast for the whole map, not one per key
	TagsManager.PushDeferOnGameplayTagTreeChangedBroadcast();
	for (const FGameplayTag& Key : Keys)
	{
		const bool bKeyInNamespace = IsKeyInNamespace(Key, AssetTagIDPrefix);
		assertIsTrue_withContinue(bKeyInNamespace);

		const FGameplayTag EntityID = TagsManager.AddNativeGameplayTag(Key.GetTagName(), TagComment);
		assertGameplayTagIsValid_withContinue(EntityID);
	}
	TagsManager.PopDeferOnGameplayTagTreeChangedBroadcast();
}

#if WITH_EDITOR
bool UEntityDataAsset_Base::NormalizeGeneratedKeys()
{
	const FName AssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(AssetTagIDName, false);

	const FString AssetTagIDPrefix = AssetTagIDName.ToString() + TEXT(".");
	const FString TagComment = FString::Printf(TEXT("(Native) Entity of DataAsset %s"), *GetPathName());

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
	TagsManager.PushDeferOnGameplayTagTreeChangedBroadcast();

	bool bChanged = false;
	for (const FMapProperty* const MapProperty : FindGeneratedKeysMaps(GetClass()))
	{
		assertIsNotNull_withContinue(MapProperty);

		FScriptMapHelper MapHelper(MapProperty, MapProperty->ContainerPtrToValuePtr<void>(this));

		TSet<FName> UsedKeyNames;
		for (FScriptMapHelper::FIterator MapIterator = MapHelper.CreateIterator(); MapIterator; ++MapIterator)
		{
			UsedKeyNames.Add(reinterpret_cast<const FGameplayTag*>(MapHelper.GetKeyPtr(MapIterator))->GetTagName());
		}

		bool bRekeyed = false;
		for (FScriptMapHelper::FIterator MapIterator = MapHelper.CreateIterator(); MapIterator; ++MapIterator)
		{
			FGameplayTag& Key = *reinterpret_cast<FGameplayTag*>(MapHelper.GetKeyPtr(MapIterator));
			if (IsKeyInNamespace(Key, AssetTagIDPrefix))
			{
				continue;
			}

			// the counter only grows; an index already taken by a key (written by hand or by a script) is skipped, not reused
			FName NewKeyName;
			do
			{
				NewKeyName = FName(AssetTagIDPrefix + FString::Printf(TEXT("%u"), IndexCounter));
				++IndexCounter;
			}
			while (UsedKeyNames.Contains(NewKeyName));
			UsedKeyNames.Add(NewKeyName);

			const FGameplayTag NewKey = TagsManager.AddNativeGameplayTag(NewKeyName, TagComment);
			assertGameplayTagIsValid_withContinue(NewKey);

			Key = NewKey;
			bRekeyed = true;
		}

		// keys were rewritten in place — the hash no longer matches them
		if (bRekeyed)
		{
			MapHelper.Rehash();
			bChanged = true;
		}
	}

	// a new DA gets its tag ID with its first element
	if (bChanged)
	{
		RegisterAllIDsAsNativeGameplayTags();
	}

	TagsManager.PopDeferOnGameplayTagTreeChangedBroadcast();

	return bChanged;
}

void UEntityDataAsset_Base::RebaseGeneratedKeys(const FString& OldAssetTagIDString,
                                                TArray<TPair<FName, FName>>& OutRenamedTags)
{
	assertStringIsNotEmpty_return(OldAssetTagIDString);

	const FName NewAssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(NewAssetTagIDName);

	const FString OldPrefix = OldAssetTagIDString + TEXT(".");
	const FString NewPrefix = NewAssetTagIDName.ToString() + TEXT(".");
	const FString TagComment = FString::Printf(TEXT("(Native) Entity of DataAsset %s"), *GetPathName());

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
	TagsManager.PushDeferOnGameplayTagTreeChangedBroadcast();

	for (const FMapProperty* const MapProperty : FindGeneratedKeysMaps(GetClass()))
	{
		assertIsNotNull_withContinue(MapProperty);

		FScriptMapHelper MapHelper(MapProperty, MapProperty->ContainerPtrToValuePtr<void>(this));

		bool bRekeyed = false;
		for (FScriptMapHelper::FIterator MapIterator = MapHelper.CreateIterator(); MapIterator; ++MapIterator)
		{
			FGameplayTag& Key = *reinterpret_cast<FGameplayTag*>(MapHelper.GetKeyPtr(MapIterator));

			const FString KeyString = Key.GetTagName().ToString();
			if (!IsKeyInNamespace(Key, OldPrefix))
			{
				continue;
			}

			// the index part stays: only the DA tag ID in front of it changes
			const FName NewKeyName = FName(NewPrefix + KeyString.RightChop(OldPrefix.Len()));

			const FGameplayTag NewKey = TagsManager.AddNativeGameplayTag(NewKeyName, TagComment);
			assertGameplayTagIsValid_withContinue(NewKey);

			OutRenamedTags.Emplace(Key.GetTagName(), NewKeyName);

			Key = NewKey;
			bRekeyed = true;
		}

		if (bRekeyed)
		{
			MapHelper.Rehash();
		}
	}

	TagsManager.PopDeferOnGameplayTagTreeChangedBroadcast();
}

FString UEntityDataAsset_Base::FindForeignAssetTagIDOfKeys() const
{
	const FGameplayTag RootTag = GetNativeTags().GetRootTag();
	assertGameplayTagIsValid_return(RootTag, FString());

	const FName AssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(AssetTagIDName, FString());

	const FString RootPrefix = RootTag.ToString() + TEXT(".");
	const FString OwnPrefix = AssetTagIDName.ToString() + TEXT(".");

	TSet<FString> ForeignAssetTagIDs;
	for (const FMapProperty* const MapProperty : FindGeneratedKeysMaps(GetClass()))
	{
		assertIsNotNull_withContinue(MapProperty);

		const FScriptMapHelper MapHelper(MapProperty, MapProperty->ContainerPtrToValuePtr<void>(this));
		for (FScriptMapHelper::FIterator MapIterator = MapHelper.CreateIterator(); MapIterator; ++MapIterator)
		{
			const FGameplayTag& Key = *reinterpret_cast<const FGameplayTag*>(MapHelper.GetKeyPtr(MapIterator));
			if (IsKeyInNamespace(Key, OwnPrefix) || !IsKeyInNamespace(Key, RootPrefix))
			{
				continue;
			}

			// [Root].[AssetName].[Index]: an asset name holds no dot, so the DA tag ID ends at the first dot after the root
			const FString KeyString = Key.GetTagName().ToString();
			const int32 IndexDot = KeyString.Find(TEXT("."), ESearchCase::CaseSensitive, ESearchDir::FromStart, RootPrefix.Len());
			if (IndexDot != INDEX_NONE)
			{
				ForeignAssetTagIDs.Add(KeyString.Left(IndexDot));
			}
		}
	}

	if (ForeignAssetTagIDs.Num() > 1)
	{
		UE_LOG(LogTypeObjectSubsystems, Warning, TEXT("%s: the keys come from %d DataAssets; none is moved — the next edit regenerates them"),
		       *GetPathName(), ForeignAssetTagIDs.Num());
		return FString();
	}

	return ForeignAssetTagIDs.IsEmpty() ? FString() : *ForeignAssetTagIDs.CreateConstIterator();
}

void UEntityDataAsset_Base::AddGameplayTagRedirects(const TArray<TPair<FName, FName>>& Redirects)
{
	if (Redirects.IsEmpty())
	{
		return;
	}

	UGameplayTagsSettings* const Settings = GetMutableDefault<UGameplayTagsSettings>();
	assertUObjectPointerIsValid_return(Settings);

	TArray<FGameplayTagRedirect>& GameplayTagRedirects = Settings->GameplayTagRedirects;

	for (const TPair<FName, FName>& Renamed : Redirects)
	{
		const FName OldTagName = Renamed.Key;
		assertNameIsAssigned_withContinue(OldTagName);

		const FName NewTagName = Renamed.Value;
		assertNameIsAssigned_withContinue(NewTagName);

		// renamed back to a former name: a redirect away from that name would loop
		GameplayTagRedirects.RemoveAll([NewTagName](const FGameplayTagRedirect& Existing) { return Existing.OldTagName == NewTagName; });

		// an earlier rename into the old name now leads to the new one — every old name resolves in one hop
		for (FGameplayTagRedirect& Existing : GameplayTagRedirects)
		{
			if (Existing.NewTagName == OldTagName)
			{
				Existing.NewTagName = NewTagName;
			}
		}

		GameplayTagRedirects.RemoveAll([OldTagName](const FGameplayTagRedirect& Existing) { return Existing.OldTagName == OldTagName; });

		FGameplayTagRedirect Redirect;
		Redirect.OldTagName = OldTagName;
		Redirect.NewTagName = NewTagName;
		GameplayTagRedirects.Add(Redirect);
	}

	// the same path as the GameplayTags editor: check the file out under revision control, otherwise only make it writable
	const FString ConfigFileName = Settings->GetDefaultConfigFilename();
	assertStringIsNotEmpty_return(ConfigFileName);

	const FString ConfigPath = FPaths::ConvertRelativePathToFull(ConfigFileName);
	const bool bSourceControlEnabled = ISourceControlModule::Get().IsEnabled();

	if (FPaths::FileExists(ConfigPath))
	{
		if (bSourceControlEnabled)
		{
			FText FailReason;
			if (!SourceControlHelpers::CheckoutOrMarkForAdd(ConfigPath, FText::FromString(ConfigPath), nullptr, FailReason))
			{
				UE_LOG(LogTypeObjectSubsystems, Error, TEXT("Cannot check out %s — %s"), *ConfigPath, *FailReason.ToString());
			}
		}
		else
		{
			FPlatformFileManager::Get().GetPlatformFile().SetReadOnly(*ConfigPath, false);
		}
	}

	if (!Settings->TryUpdateDefaultConfigFile())
	{
		UE_LOG(LogTypeObjectSubsystems, Error, TEXT("Cannot write the gameplay tag redirects to %s"), *ConfigPath);
	}

	// a file the write has just created is marked for add
	if (bSourceControlEnabled)
	{
		FText FailReason;
		if (!SourceControlHelpers::CheckoutOrMarkForAdd(ConfigPath, FText::FromString(ConfigPath), nullptr, FailReason))
		{
			UE_LOG(LogTypeObjectSubsystems, Error, TEXT("Cannot mark %s for add — %s"), *ConfigPath, *FailReason.ToString());
		}
	}

	assertIsNotNull_return(GConfig);
	GConfig->LoadFile(ConfigFileName);

	// the refresh rebuilds the tag tree and the redirect map from the settings object
	UGameplayTagsManager::Get().EditorRefreshGameplayTagTree();

	UE_LOG(LogTypeObjectSubsystems, Log, TEXT("Added %d gameplay tag redirects to %s"), Redirects.Num(), *ConfigPath);
}
#endif

FName UEntityDataAsset_Base::GetCategoryName() const
{
	return GetPrimaryAssetId().PrimaryAssetName;
}

void UEntityDataAsset_Base::RegisterAllIDsAsNativeGameplayTags() const
{
	const FName AssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(AssetTagIDName);

	const FGameplayTag AssetTagID = UGameplayTagsManager::Get().AddNativeGameplayTag(AssetTagIDName,
		FString::Printf(TEXT("(Native) DataAsset %s"), *GetPathName()));
	assertGameplayTagIsValid_return(AssetTagID);
}

FGameplayTag UEntityDataAsset_Base::GetAssetTagID() const
{
	const FName AssetTagIDName = ComposeAssetTagIDName();
	assertNameIsAssigned_return(AssetTagIDName, FGameplayTag::EmptyTag);

	// a lookup, never a registration: a getter does not change the global tag tree
	return UGameplayTagsManager::Get().RequestGameplayTag(AssetTagIDName, /*ErrorIfNotFound*/ false);
}

void UEntityDataAsset_Base::RegisterAllIDsOfClass(const TSubclassOf<UEntityDataAsset_Base> DataAssetClass)
{
	assertUObjectPointerIsValid_return(DataAssetClass);

	const UEntityDataAsset_Base* const DefaultDataAsset = DataAssetClass->GetDefaultObject<UEntityDataAsset_Base>();
	assertUObjectPointerIsValid_return(DefaultDataAsset);

	// the root comes from the class's native tag struct, whose own adder may not have run yet
	const FNativeGameplayTags_Base& NativeTags = DefaultDataAsset->GetNativeTags();
	assertCustomStructIsSet_return(NativeTags);

	if (!NativeTags.GetRootTag().IsValid())
	{
		NativeTags.RegisterTags();
	}

	const FGameplayTag RootTag = NativeTags.GetRootTag();
	assertGameplayTagIsValid_return(RootTag);

	TArray<UObject*> LoadedAssets;
	UEnhancedAssetManager::LoadSyncAllAssetsByClass(DataAssetClass, LoadedAssets);

	// the module's call and the subsystem's guard both arrive here; a DA registers once per process
	static TSet<FObjectKey> RegisteredDataAssets;

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
	TagsManager.PushDeferOnGameplayTagTreeChangedBroadcast();
	for (UObject* const LoadedAsset : LoadedAssets)
	{
		const UEntityDataAsset_Base* const DataAsset = Cast<UEntityDataAsset_Base>(LoadedAsset);
		assertUObjectPointerIsValid_withContinue(DataAsset);

		const FObjectKey DataAssetKey{DataAsset};
		if (RegisteredDataAssets.Contains(DataAssetKey))
		{
			continue;
		}

		DataAsset->RegisterAllIDsAsNativeGameplayTags();
		RegisteredDataAssets.Add(DataAssetKey);
	}
	TagsManager.PopDeferOnGameplayTagTreeChangedBroadcast();
}

void UEntityDataAsset_Base::RegisterAllIDsOfClassOnNativeTagsAdding(const TSubclassOf<UEntityDataAsset_Base> DataAssetClass)
{
	assertUObjectPointerIsValid_return(DataAssetClass);

	// the class of a module unloaded before the delegate fires must not be touched
	const TWeakObjectPtr<UClass> WeakDataAssetClass = DataAssetClass.Get();
	UGameplayTagsManager::CallOrRegister_OnAddNativeTagsDelegate(FSimpleMulticastDelegate::FDelegate::CreateLambda([WeakDataAssetClass]()
	{
		IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();

		// the editor gathers the asset registry asynchronously: at the end of engine start-up it cannot finish yet
		// (WaitForCompletion gives up while IsEngineStartupModuleLoadingComplete is false) and finds no DA, so the editor
		// registers when the initial gather is over; a cooked game's registry is complete from the start and registers now
		if (AssetRegistry.IsLoadingAssets())
		{
			const TSharedRef<FDelegateHandle> FilesLoadedHandle = MakeShared<FDelegateHandle>();
			*FilesLoadedHandle = AssetRegistry.OnFilesLoaded().AddLambda([WeakDataAssetClass, FilesLoadedHandle]()
			{
				IAssetRegistry::GetChecked().OnFilesLoaded().Remove(*FilesLoadedHandle);

				UClass* const DataAssetClassToRegister = WeakDataAssetClass.Get();
				if (DataAssetClassToRegister != nullptr)
				{
					RegisterAllIDsOfClass(DataAssetClassToRegister);
				}
			});
			return;
		}

		UClass* const DataAssetClassToRegister = WeakDataAssetClass.Get();
		if (DataAssetClassToRegister != nullptr)
		{
			RegisterAllIDsOfClass(DataAssetClassToRegister);
		}
	}));
}
