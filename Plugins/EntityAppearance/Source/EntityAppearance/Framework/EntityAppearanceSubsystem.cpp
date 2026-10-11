// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/EntityAppearanceSubsystem.h"

#include "Framework/EntityAppearanceDataAsset.h"

TSubclassOf<UFacetDataAsset_Base> UEntityAppearanceSubsystem::GetDataAssetClass() const
{
	return UEntityAppearanceDataAsset::StaticClass();
}

bool UEntityAppearanceSubsystem::HasAppearance(const FGameplayTag& Id) const
{
	return ContainsId(Id);
}

const FEntityAppearanceData& UEntityAppearanceSubsystem::GetAppearance(const FGameplayTag& Id) const
{
	// the DA of the ID's root (one DA per entity subsystem); FindDataAssetById reports a missing DA, the DA an ID it does not hold
	const UFacetDataAsset_Base* const DataAsset = FindDataAssetById(Id);
	if (DataAsset == nullptr)
	{
		return FEntityAppearanceData::EmptyData;
	}

	// the base keys only GetDataAssetClass instances
	return CastChecked<UEntityAppearanceDataAsset>(DataAsset)->FindAppearance(Id);
}
