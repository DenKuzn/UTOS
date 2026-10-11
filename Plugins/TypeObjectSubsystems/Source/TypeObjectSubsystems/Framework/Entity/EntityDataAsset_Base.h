// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "Framework/Tags/NativeGameplayTags_Base.h"

#include "EntityDataAsset_Base.generated.h"

class FDataValidationContext;
struct FPropertyChangedEvent;

/** Base of every DataAsset that stores entity descriptions for a description subsystem.
 *  Classification: the DA class is the entity type, a DA instance is a category, a map inside it is a subcategory,
 *  a map element is the entity. An entity has no category field — its category is the DA it sits in,
 *  keyed by the primary asset name (GetCategoryName).
 *  The primary asset type is the concrete class name, so the AssetManager scan rule in the
 *  plugin's Config/Game.ini names the class and nothing else has to agree with it.
 *  Identity: the DA tag ID is [Root].[AssetName], the root read from the DA class's native tag struct (GetNativeTags);
 *  entity IDs are the keys of the DA's maps, composed under the DA tag ID: [DA tag ID].[Index].
 *  The DA never reaches its subsystem — the subsystem asks the DA for its tag ID.
 *  Registration: the module that owns a DA class calls RegisterAllIDsOfClassOnNativeTagsAdding from StartupModule;
 *  each DA registers its own IDs (RegisterAllIDsAsNativeGameplayTags).
 *  Generated keys (editor only): a top-level TMap<FGameplayTag, *> marked meta = (UTOSGeneratedKeys, ReadOnlyKeys)
 *  gets every new key from IndexCounter. Renaming the asset moves its tag ID and keys under the new name and writes
 *  gameplay tag redirects; duplicating it moves the copy's keys under the copy's name.
 *  Descriptions are read only through the owning subsystem — never from the DA directly. */
UCLASS(Abstract)
class TYPEOBJECTSUBSYSTEMS_API UEntityDataAsset_Base : public UPrimaryDataAsset
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void PostRename(UObject* OldOuter, const FName OldName) override;

	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;

#if WITH_EDITOR
	virtual void PostLoad() override;

	virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PostEditUndo() override;

	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

	/**
	 * Returns the native tag struct of the subsystem this DA class belongs to — the source of the root tag.
	 * Override once, in the plugin's DA class, mark it final and return the struct's Get():
	 *     virtual const FNativeGameplayTags_Base& GetNativeTags() const override final { return FItemSubsystemTags::Get(); }
	 * Only the DA reads it: the owning subsystem never sees the root, it stores the DA under GetAssetTagID.
	 */
	virtual const FNativeGameplayTags_Base& GetNativeTags() const PURE_VIRTUAL(UEntityDataAsset_Base::GetNativeTags, return FNativeGameplayTags_Base::EmptyData;);

// ============================================================
// Class Fields
// ============================================================
private:
#if WITH_EDITORONLY_DATA
	/** Index the next generated key takes; +1 after each. The only source of truth: never recomputed from the keys and
	 *  never decremented — removing elements or clearing a map leaves it as is, so an index is never handed out twice.
	 *  Saved in the asset, hidden from the details panel, absent from game builds; NonTransactional so undo never rolls it back. */
	UPROPERTY(NonTransactional)
	uint32 IndexCounter = 0;

	/** IndexCounter as last loaded from or saved to disk. An undo leaves a package clean if it was clean before the change,
	 *  so a counter advanced by an undone add would never be saved; this tells PostEditUndo that the package must stay dirty.
	 *  Without it, after a restart the counter falls back and the index of the undone element is issued again —
	 *  references made to that ID in the meantime silently point at a new entity. */
	UPROPERTY(Transient, NonTransactional)
	uint32 SavedIndexCounter = 0;
#endif

// ============================================================
// Private Functions
// ============================================================
private:
	/** Returns the name of the DA tag ID: [Root].[AssetName]; None when the root or the asset name is missing or the name is not a valid tag. */
	FName ComposeAssetTagIDName() const;

	/**
	 * Registers every key that lies in this DA's namespace ([DA tag ID].*) as a native gameplay tag; logs and skips the rest.
	 * @param Keys The keys of one of the DA's maps.
	 */
	void RegisterKeysAsNativeGameplayTags(TConstArrayView<FGameplayTag> Keys) const;

#if WITH_EDITOR
	/**
	 * Gives every key of the marked maps that is empty or outside this DA's namespace a fresh key [DA tag ID].[IndexCounter]
	 * and registers it; registers all IDs of the DA when anything changed.
	 * @return True if a key was replaced.
	 */
	bool NormalizeGeneratedKeys();

	/**
	 * Moves every key of the marked maps that lies under the old DA tag ID under the current one, keeping its index, and registers it.
	 * @param OldAssetTagIDString The DA tag ID the keys were generated under.
	 * @param OutRenamedTags Receives each moved key as old name → new name.
	 */
	void RebaseGeneratedKeys(const FString& OldAssetTagIDString,
	                         TArray<TPair<FName, FName>>& OutRenamedTags);

	/** Returns the DA tag ID the keys of the marked maps were generated under when it is not this DA's own one — the source of a duplicate;
	 *  empty when every key is this DA's own or the keys come from more than one DA. */
	FString FindForeignAssetTagIDOfKeys() const;

	/**
	 * Adds gameplay tag redirects old → new to the project's DefaultGameplayTags.ini, the way the GameplayTags editor does it,
	 * and refreshes the tag tree so the running editor applies them.
	 * @param Redirects Old tag name → new tag name.
	 */
	static void AddGameplayTagRedirects(const TArray<TPair<FName, FName>>& Redirects);
#endif

protected:
	/**
	 * Registers the keys of one of the DA's maps as native gameplay tags. For a child's RegisterAllIDsAsNativeGameplayTags.
	 * @param Map A map of the DA keyed by entity ID.
	 */
	template <typename ValueType>
	void RegisterMapKeysAsNativeGameplayTags(const TMap<FGameplayTag, ValueType>& Map) const
	{
		TArray<FGameplayTag> Keys;
		Map.GenerateKeyArray(Keys);
		RegisterKeysAsNativeGameplayTags(Keys);
	}

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the category key of every entity in this DA: the primary asset name.
	 */
	FName GetCategoryName() const;

	/**
	 * Registers the DA tag ID [Root].[AssetName] as a native gameplay tag; the DA tag ID exists even when the DA holds no entities.
	 * A child with entity maps overrides it: calls Super, then RegisterMapKeysAsNativeGameplayTags for each map.
	 */
	virtual void RegisterAllIDsAsNativeGameplayTags() const;

	/**
	 * Returns the DA tag ID [Root].[AssetName] — the key the owning subsystem stores this DA under.
	 * Empty until RegisterAllIDsAsNativeGameplayTags has run: a tag that is not registered does not exist.
	 */
	FGameplayTag GetAssetTagID() const;

	/**
	 * Loads every DA of the class and of its subclasses and registers the IDs of each one not registered yet;
	 * first registers the class's native tags so the root exists. Safe to call again: a DA registers once.
	 * @param DataAssetClass The DA class of an entity subsystem.
	 */
	static void RegisterAllIDsOfClass(const TSubclassOf<UEntityDataAsset_Base> DataAssetClass);

	/**
	 * Runs RegisterAllIDsOfClass when native gameplay tags are added: at the end of engine start-up, or at the end of the current
	 * module load when start-up is over; while the asset registry is still gathering (the editor at start-up) — once its initial
	 * gather is over. The one call a plugin's StartupModule makes for its DA class — loading assets inside StartupModule itself
	 * is unsafe, the engine is not initialized yet.
	 * @param DataAssetClass The DA class of an entity subsystem.
	 */
	static void RegisterAllIDsOfClassOnNativeTagsAdding(const TSubclassOf<UEntityDataAsset_Base> DataAssetClass);
};
