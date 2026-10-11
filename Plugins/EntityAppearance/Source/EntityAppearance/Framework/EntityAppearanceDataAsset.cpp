// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/EntityAppearanceDataAsset.h"

#include "AssertUtils/Assert.h"

void UEntityAppearanceDataAsset::CollectIds(TArray<FGameplayTag>& Out_Ids) const
{
	Appearances.GenerateKeyArray(Out_Ids);
}

bool UEntityAppearanceDataAsset::ContainsId(const FGameplayTag& Id) const
{
	return Appearances.Contains(Id);
}

const FEntityAppearanceData& UEntityAppearanceDataAsset::FindAppearance(const FGameplayTag& Id) const
{
	const FEntityAppearanceData* const Appearance = Appearances.Find(Id);
	assertIsNotNull_return(Appearance, FEntityAppearanceData::EmptyData);

	return *Appearance;
}
