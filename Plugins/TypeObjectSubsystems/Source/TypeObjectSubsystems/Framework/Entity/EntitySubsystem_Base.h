// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "EntitySubsystem_Base.generated.h"

class UEntityDataAsset_Base;
class UPrimaryDataAsset;

TYPEOBJECTSUBSYSTEMS_API DECLARE_LOG_CATEGORY_EXTERN(LogTypeObjectSubsystems, Log, All);

/** Base of every entity subsystem — a description subsystem that owns its entities and their IDs (UE Type Object Subsystems pattern).
 *  Facets — aspects of objects owned elsewhere — derive from UFacetSubsystem_Base instead.
 *  A game instance subsystem: it lives with its game instance. Reach it through the game instance.
 *  Loads every DataAsset of the child's class (GetDataAssetClass) once at Initialize and stores each under the tag ID
 *  the DA reports (UEntityDataAsset_Base::GetAssetTagID). The DAs are reachable only from the subsystem: a child reads them
 *  through the protected FindDataAsset, nothing outside the subsystem gets a DA.
 *  Tags are the DA's business: the module that owns the DA class registers the IDs (UEntityDataAsset_Base::RegisterAllIDsOfClassOnNativeTagsAdding);
 *  the subsystem only stores the DAs. */
UCLASS(Abstract)
class TYPEOBJECTSUBSYSTEMS_API UEntitySubsystem_Base : public UGameInstanceSubsystem
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
	 * Returns every DataAsset loaded at Initialize, in no particular order.
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
	/** DA tag ID ([Root].[AssetName]) → the DA. Also keeps the loaded DataAssets alive for the subsystem's lifetime,
	 *  since otherwise GC can collect them in a packaged build. */
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UEntityDataAsset_Base>> LoadedDataAssets;

// ============================================================
// Private Functions
// ============================================================
private:
	/**
	 * Stores each DA under the tag ID it reports.
	 * @param DataAssets The loaded DataAssets, each an instance of GetDataAssetClass.
	 */
	void StoreDataAssets(const TArray<UEntityDataAsset_Base*>& DataAssets);

protected:
	/** Returns the DataAsset class this subsystem reads its descriptions from; every asset of it and of its subclasses is loaded at Initialize. */
	virtual TSubclassOf<UEntityDataAsset_Base> GetDataAssetClass() const PURE_VIRTUAL(UEntitySubsystem_Base::GetDataAssetClass, return nullptr;);

	/**
	 * Returns the loaded DataAsset stored under the DA tag ID; nullptr with an assert for an unknown tag ID.
	 * The child casts it to its DA class.
	 * @param AssetTagID The DA tag ID [Root].[AssetName] — for an entity ID, its parent tag.
	 */
	const UEntityDataAsset_Base* FindDataAsset(const FGameplayTag& AssetTagID) const;
};
