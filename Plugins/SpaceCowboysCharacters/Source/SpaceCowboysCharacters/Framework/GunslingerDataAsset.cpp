// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/GunslingerDataAsset.h"

#include "AssertUtils/Assert.h"

#include "Framework/NGT_GunslingerTags.h"

const FNativeGameplayTags_Base& UGunslingerDataAsset::GetNativeTags() const
{
	return FNGT_GunslingerTags::Get();
}

void UGunslingerDataAsset::RegisterAllIDsAsNativeGameplayTags() const
{
	Super::RegisterAllIDsAsNativeGameplayTags();

	RegisterMapKeysAsNativeGameplayTags(Gunslingers);
}

const FGunslingerData& UGunslingerDataAsset::FindGunslinger(const FGameplayTag& Id) const
{
	assertGameplayTagIsValid_return(Id, FGunslingerData::EmptyData);

	const FGunslingerData* const GunslingerData = Gunslingers.Find(Id);
	assertIsNotNull_return(GunslingerData, FGunslingerData::EmptyData);

	return *GunslingerData;
}
