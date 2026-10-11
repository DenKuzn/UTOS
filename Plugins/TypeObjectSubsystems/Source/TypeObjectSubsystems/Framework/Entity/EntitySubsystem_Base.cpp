// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Entity/EntitySubsystem_Base.h"

#include "AssertUtils/Assert.h"

#include "Framework/AssetManager/EnhancedAssetManager.h"
#include "Framework/Entity/EntityDataAsset_Base.h"

DEFINE_LOG_CATEGORY(LogTypeObjectSubsystems);

TArray<const UPrimaryDataAsset*> UEntitySubsystem_Base::DEBUG_GetLoadedDataAssets() const
{
	TArray<const UPrimaryDataAsset*> DataAssets;
	DataAssets.Reserve(LoadedDataAssets.Num());
	for (const TPair<FGameplayTag, TObjectPtr<UEntityDataAsset_Base>>& Entry : LoadedDataAssets)
	{
		assertUObjectPointerIsValid_withContinue(Entry.Value);

		DataAssets.Add(Entry.Value.Get());
	}

	return DataAssets;
}

void UEntitySubsystem_Base::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const TSubclassOf<UEntityDataAsset_Base> DataAssetClass = GetDataAssetClass();
	assertUObjectPointerIsValid_return(DataAssetClass);

	// guard, not registration of the subsystem's own: a packaged game initializes game instance subsystems before
	// OnPostEngineInit (GameEngine.cpp InitializeStandalone, then LaunchEngineLoop.cpp), i.e. before the owning module's
	// registration has run; the helper registers each DA once, so the module's later call does nothing
	UEntityDataAsset_Base::RegisterAllIDsOfClass(DataAssetClass);

	TArray<UObject*> SynchronousLoadedAssets;
	UEnhancedAssetManager::LoadSyncAllAssetsByClass(DataAssetClass, SynchronousLoadedAssets);

	// raw pointers for the child; the field keeps the same objects alive
	TArray<UEntityDataAsset_Base*> DataAssets;
	DataAssets.Reserve(SynchronousLoadedAssets.Num());
	for (UObject* const LoadedAsset : SynchronousLoadedAssets)
	{
		assertUObjectPointerIsValid_withContinue(LoadedAsset);
		assertIsTrue_withContinue(LoadedAsset->IsA(DataAssetClass));

		DataAssets.Add(CastChecked<UEntityDataAsset_Base>(LoadedAsset));
	}

	// storing is the base's, not an overridable hook: a child that forgets Super cannot skip it
	StoreDataAssets(DataAssets);
}

void UEntitySubsystem_Base::StoreDataAssets(const TArray<UEntityDataAsset_Base*>& DataAssets)
{
	for (UEntityDataAsset_Base* const DataAsset : DataAssets)
	{
		assertUObjectPointerIsValid_withContinue(DataAsset);

		// the subsystem never composes the DA tag ID — it asks the DA
		const FGameplayTag AssetTagID = DataAsset->GetAssetTagID();
		assertGameplayTagIsValid_withContinue(AssetTagID);

		assertIsNull_withContinue(LoadedDataAssets.Find(AssetTagID));

		LoadedDataAssets.Add(AssetTagID, DataAsset);
	}
}

const UEntityDataAsset_Base* UEntitySubsystem_Base::FindDataAsset(const FGameplayTag& AssetTagID) const
{
	assertGameplayTagIsValid_return(AssetTagID, nullptr);

	const TObjectPtr<UEntityDataAsset_Base>* const DataAsset = LoadedDataAssets.Find(AssetTagID);
	assertIsNotNull_return(DataAsset, nullptr);
	assertUObjectPointerIsValid_return(*DataAsset, nullptr);

	return DataAsset->Get();
}