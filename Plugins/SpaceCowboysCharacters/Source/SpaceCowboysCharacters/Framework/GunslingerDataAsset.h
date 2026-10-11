// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Entity/EntityDataAsset_Base.h"

#include "Framework/Data/GunslingerData.h"

#include "GunslingerDataAsset.generated.h"

/** Gunslingers of one race: the DA instance is the race, a map element is a gunslinger.
 *  The DA tag ID is Gunslinger.<AssetName>; the key of an element is the gunslinger's ID, Gunslinger.<AssetName>.<Index>.
 *  Keys are generated in the editor from the DA's counter and never reused, so removing a gunslinger changes no other ID.
 *  Read only through UGunslingerSubsystem. */
UCLASS()
class SPACECOWBOYSCHARACTERS_API UGunslingerDataAsset : public UEntityDataAsset_Base
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
	virtual const FNativeGameplayTags_Base& GetNativeTags() const override final;

	virtual void RegisterAllIDsAsNativeGameplayTags() const override;

// ============================================================
// Class Fields
// ============================================================
private:
	/** Gunslinger ID → description. A new element gets its key automatically; keys cannot be edited by hand. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslingers", meta = (UTOSGeneratedKeys, ReadOnlyKeys))
	TMap<FGameplayTag, FGunslingerData> Gunslingers;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the description of the gunslinger; EmptyData with an assert when this DA has no such ID.
	 * @param Id The gunslinger ID, Gunslinger.<AssetName>.<Index>.
	 */
	const FGunslingerData& FindGunslinger(const FGameplayTag& Id) const;
};
