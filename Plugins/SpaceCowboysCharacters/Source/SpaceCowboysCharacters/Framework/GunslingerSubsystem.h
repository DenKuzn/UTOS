// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Framework/Entity/EntitySubsystem_Base.h"

#include "Framework/Data/GunslingerData.h"

#include "GunslingerSubsystem.generated.h"

/** Entity subsystem of the gunslingers: owns every gunslinger description and its ID.
 *  The base loads every UGunslingerDataAsset at Initialize; the IDs are registered by the module (UEntityDataAsset_Base::RegisterAllIDsOfClass).
 *  Gunslinger data is read only here, by ID; the DAs themselves never leave the subsystem. */
UCLASS()
class SPACECOWBOYSCHARACTERS_API UGunslingerSubsystem : public UEntitySubsystem_Base
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
protected:
	virtual TSubclassOf<UEntityDataAsset_Base> GetDataAssetClass() const override;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the description of the gunslinger; EmptyData with an assert for an unknown ID.
	 * @param Id The gunslinger ID, Gunslinger.<AssetName>.<Index>.
	 */
	const FGunslingerData& GetGunslingerData(const FGameplayTag& Id) const;
};
