// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/GunslingerSubsystem.h"

#include "AssertUtils/Assert.h"

#include "Framework/GunslingerDataAsset.h"

TSubclassOf<UEntityDataAsset_Base> UGunslingerSubsystem::GetDataAssetClass() const
{
	return UGunslingerDataAsset::StaticClass();
}

const FGunslingerData& UGunslingerSubsystem::GetGunslingerData(const FGameplayTag& Id) const
{
	assertGameplayTagIsValid_return(Id, FGunslingerData::EmptyData);

	// the parent of a gunslinger ID is the tag ID of the DA that holds it
	const FGameplayTag AssetTagID = Id.RequestDirectParent();
	assertGameplayTagIsValid_return(AssetTagID, FGunslingerData::EmptyData);

	const UEntityDataAsset_Base* const DataAsset = FindDataAsset(AssetTagID);
	assertUObjectPointerIsValid_return(DataAsset, FGunslingerData::EmptyData);

	// the base loads only GetDataAssetClass instances; the DA reports an unknown gunslinger ID
	return CastChecked<UGunslingerDataAsset>(DataAsset)->FindGunslinger(Id);
}
