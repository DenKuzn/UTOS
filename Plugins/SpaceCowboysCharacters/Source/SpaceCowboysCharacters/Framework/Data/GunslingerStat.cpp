// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Data/GunslingerStat.h"

#include "AssertUtils/Assert.h"

#include "Framework/Data/GunslingerData.h"

const FGunslingerStat FGunslingerStat::EmptyData{};

FGunslingerStat::~FGunslingerStat()
{
}

bool FGunslingerStat::IsSet() const
{
	return *this != EmptyData;
}

int32 FGunslingerStat::GetBaseValue() const
{
	return BaseValue;
}

int32 FGunslingerStat::GetEvaluatedStat(const FGunslingerData& GunslingerData,
                                        const FGameplayTagContainer& CurrentEffectsOnGunslinger) const
{
	assertCustomStructIsSet_return((*this), UnsetStatValue);

	return BaseValue;
}
