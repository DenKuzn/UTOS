// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "FacetSubsystem_Base.generated.h"

class UFacetDataAsset_Base;
class UPrimaryDataAsset;

/** Base of every facet subsystem — a description subsystem that describes one aspect (appearance, ...) of objects
 *  it does not own, keyed by their IDs. Owns no entities and no ID root; entity subsystems derive from UEntitySubsystem_Base.
 *  Rule: one DA per entity subsystem. Loads every DataAsset of the child's class (GetDataAssetClass) once at Initialize
 *  and keys each by its root (UFacetDataAsset_Base::GetRootName, e.g. Gunslinger). A lookup takes the root of the ID,
 *  finds the DA by it, then the entry by the full ID. Registers no tags.
 *  A game instance subsystem: it lives with its game instance. Reach it through the game instance. */
UCLASS(Abstract)
class TYPEOBJECTSUBSYSTEMS_API UFacetSubsystem_Base : public UGameInstanceSubsystem
{
	GENERATED_BODY()

// ============================================================
// Debug Section
// ============================================================
public:
	/**
	 * DEBUG function — for debug tools only; game code must not call it. DataAssets never leave their subsystem
	 * otherwise: this accessor is the single exception, kept in every build configuration (Shipping included)
	 * so on-screen debug tools work in a packaged game.
	 * Returns every keyed DataAsset. A DA without a root is not keyed (AddDataAsset asserts on it), so it is not listed.
	 */
	TArray<const UPrimaryDataAsset*> DEBUG_GetLoadedDataAssets() const;

// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

// ============================================================
// Class Fields
// ============================================================
private:
	/** Root of an entity subsystem (e.g. Gunslinger) → the DataAsset that describes its entities.
	 *  An FName, not a tag: at Initialize the roots may not be registered as tags yet.
	 *  The only DA storage: it also keeps the DataAssets alive for the subsystem's lifetime,
	 *  since otherwise GC can collect them in a packaged build. */
	UPROPERTY()
	TMap<FName, TObjectPtr<UFacetDataAsset_Base>> DataAssetByRoot;

// ============================================================
// Private Functions
// ============================================================
private:
	/**
	 * Keys the DataAsset by its root. A DA without a root (empty, or keys under different roots) is a data error: asserted, not keyed.
	 * A root already taken stays with the first DA and is reported.
	 * @param DataAsset A loaded DataAsset of GetDataAssetClass.
	 */
	void AddDataAsset(UFacetDataAsset_Base* DataAsset);

protected:
	/** Returns the DataAsset class this subsystem reads its descriptions from; every asset of it and of its subclasses is loaded at Initialize. */
	virtual TSubclassOf<UFacetDataAsset_Base> GetDataAssetClass() const PURE_VIRTUAL(UFacetSubsystem_Base::GetDataAssetClass, return nullptr;);

	/**
	 * Returns the DataAsset of the ID's root; nullptr with an assert when no DA describes that root — a request error
	 * (ask ContainsId first when "no data" is a valid answer). The DA may still lack this exact ID — it reports that itself.
	 * The child casts it to its DA class.
	 * @param Id The entity ID.
	 */
	const UFacetDataAsset_Base* FindDataAssetById(const FGameplayTag& Id) const;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns true if a loaded DataAsset holds data for the ID. No assert: a caller may ask about any entity.
	 * @param Id The entity ID.
	 */
	bool ContainsId(const FGameplayTag& Id) const;
};
