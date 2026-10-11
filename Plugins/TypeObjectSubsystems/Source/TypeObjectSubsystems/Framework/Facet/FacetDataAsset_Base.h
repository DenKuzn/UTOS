// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "FacetDataAsset_Base.generated.h"

/** Base of every DataAsset a facet subsystem reads: one aspect (appearance, text, ...) of entities owned by entity subsystems,
 *  keyed by their IDs. Registers no tags — the IDs it is keyed by belong to the entity subsystems.
 *  Rule: one facet DA per entity subsystem. Every key of a DA lies under the same root — the first segment of the ID,
 *  the root of the entity subsystem (e.g. Gunslinger) — and the facet subsystem indexes the DA by that root (GetRootName).
 *  The primary asset type is the concrete class name (the UPrimaryDataAsset default), so the AssetManager scan rule
 *  in the plugin's Config/Game.ini names the class. */
UCLASS(Abstract)
class TYPEOBJECTSUBSYSTEMS_API UFacetDataAsset_Base : public UPrimaryDataAsset
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
#if WITH_EDITOR
	/** Insurance while editing: once the map holds two or more keys, a key under another root is reported the moment it appears. */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

// ============================================================
// Private Functions
// ============================================================
private:
	/**
	 * Returns the root shared by every key; NAME_None when there is no key, NAME_None with an assert when the keys lie under different roots.
	 * Keys not set yet (an element just added in the editor) are skipped.
	 * @param Ids The keys of this DA.
	 */
	static FName FindCommonRootName(const TArray<FGameplayTag>& Ids);

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the root of an ID: its first segment, read from the tag name (Gunslinger.DA_SCC_Human.3 → Gunslinger).
	 * Read from the name, not the tag tree: at a facet's Initialize the entity IDs may not be registered yet.
	 * @param Id The entity ID.
	 * @param FindType FNAME_Find for a lookup (an unknown root gives NAME_None), FNAME_Add when building the index.
	 */
	static FName GetRootNameOf(const FGameplayTag& Id, const EFindName FindType = FNAME_Find);

	/**
	 * Returns the root of this DA after checking every key lies under it; NAME_None for an empty DA,
	 * NAME_None with an assert when the keys lie under different roots — such a DA must not be indexed.
	 */
	FName GetRootName() const;

	/**
	 * Fills the IDs this DA holds data for — the keys of its map.
	 * @param Out_Ids Receives the IDs.
	 */
	virtual void CollectIds(TArray<FGameplayTag>& Out_Ids) const PURE_VIRTUAL(UFacetDataAsset_Base::CollectIds, );

	/**
	 * Returns true if this DA holds data for the ID. No assert: a caller may ask about any entity.
	 * @param Id The entity ID.
	 */
	virtual bool ContainsId(const FGameplayTag& Id) const PURE_VIRTUAL(UFacetDataAsset_Base::ContainsId, return false;);
};
