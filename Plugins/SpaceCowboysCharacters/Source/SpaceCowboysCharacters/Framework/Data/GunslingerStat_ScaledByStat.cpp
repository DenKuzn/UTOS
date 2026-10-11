// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Data/GunslingerStat_ScaledByStat.h"

#include "AssertUtils/Assert.h"

#include "Framework/Data/GunslingerData.h"

namespace GunslingerStat_ScaledByStat
{
	// the scaling stat adds to the own base value only while its evaluated value is strictly greater than this
	constexpr int32 ScalingThreshold = 2;

	// the scaling stat adds its evaluated value divided by this, rounded down
	constexpr int32 ScalingDivisor = 2;
}

const FGunslingerStat_ScaledByStat FGunslingerStat_ScaledByStat::EmptyData{};

int32 FGunslingerStat_ScaledByStat::GetEvaluatedStat(const FGunslingerData& GunslingerData,
                                                     const FGameplayTagContainer& CurrentEffectsOnGunslinger) const
{
	const FGunslingerStat& OwnBaseStat = *this;
	assertCustomStructIsSet_return(OwnBaseStat, UnsetStatValue);

	// TODO(assert): valid range of OwnBaseValue unknown
	const int32 OwnBaseValue = GetBaseValue();

	assertCustomStructIsSet_return(GunslingerData, OwnBaseValue);

	assertGameplayTagIsValid_return(ScalingStat, OwnBaseValue);

	const FGunslingerStat& ScalingStatData = GunslingerData.GetStat(ScalingStat);
	assertCustomStructIsSet_return(ScalingStatData, OwnBaseValue);

	assertIsTrue_return(&ScalingStatData != this, OwnBaseValue);

	// the evaluated value, not the base one: the scaling stat may change at runtime (a wound, a buff);
	// it is evaluated under the same effects as this stat
	// TODO(assert): valid range of ScalingValue unknown
	const int32 ScalingValue = ScalingStatData.GetEvaluatedStat(GunslingerData, CurrentEffectsOnGunslinger);
	if (ScalingValue > GunslingerStat_ScaledByStat::ScalingThreshold)
	{
		return OwnBaseValue + ScalingValue / GunslingerStat_ScaledByStat::ScalingDivisor;
	}

	return OwnBaseValue;
}

bool FGunslingerStat_ScaledByStat::IsSet() const
{
	return *this != EmptyData;
}
