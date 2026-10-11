// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Facet/FacetDataAsset_Base.h"

#include "Framework/EntityAppearanceData.h"

#include "EntityAppearanceDataAsset.generated.h"

/** Appearances of entities keyed by the entity ID of any entity subsystem.
 *  Read only through UEntityAppearanceSubsystem. A project usually keeps one such DA per entity kind. */
UCLASS()
class ENTITYAPPEARANCE_API UEntityAppearanceDataAsset : public UFacetDataAsset_Base
{
	GENERATED_BODY()

// ============================================================
// Class Fields
// ============================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
	TMap<FGameplayTag, FEntityAppearanceData> Appearances;

// ============================================================
// Public Interface
// ============================================================
public:
	virtual void CollectIds(TArray<FGameplayTag>& Out_Ids) const override;

	virtual bool ContainsId(const FGameplayTag& Id) const override;

	/**
	 * Returns the appearance held under the entity ID; EmptyData with an assert when this DA has no such ID.
	 * @param Id The entity ID of any entity subsystem.
	 */
	const FEntityAppearanceData& FindAppearance(const FGameplayTag& Id) const;
};
