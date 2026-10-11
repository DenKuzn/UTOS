// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Data/GunslingerStat_HalvedByEffect.h"

#include "AssertUtils/Assert.h"

#include "Framework/Data/GunslingerData.h"

namespace GunslingerStat_HalvedByEffect
{
	// under the halving effect a positive base value is divided by this, rounded toward zero
	constexpr int32 HalvingDivisor = 2;

	// under the halving effect a negative base value (a penalty) is multiplied by 1.5 = Numerator / Denominator,
	// rounded down — away from zero for a negative value, so the penalty only gets stronger: -5 → -8
	constexpr int32 PenaltyMultiplierNumerator = 3;
	constexpr int32 PenaltyMultiplierDenominator = 2;
}

const FGunslingerStat_HalvedByEffect FGunslingerStat_HalvedByEffect::EmptyData{};

int32 FGunslingerStat_HalvedByEffect::GetEvaluatedStat(const FGunslingerData& GunslingerData,
                                                       const FGameplayTagContainer& CurrentEffectsOnGunslinger) const
{
	const FGunslingerStat& OwnBaseStat = *this;
	assertCustomStructIsSet_return(OwnBaseStat, UnsetStatValue);

	// TODO(assert): valid range of OwnBaseValue unknown
	const int32 OwnBaseValue = GetBaseValue();

	assertGameplayTagIsValid_return(HalvingEffect, OwnBaseValue);

	// hierarchical match: a child of the halving effect halves the stat too
	if (!CurrentEffectsOnGunslinger.HasTag(HalvingEffect))
	{
		return OwnBaseValue;
	}

	// a bonus is halved; a zero stays zero
	if (OwnBaseValue >= 0)
	{
		return OwnBaseValue / GunslingerStat_HalvedByEffect::HalvingDivisor;
	}

	// a penalty grows by half: integer division truncates toward zero, so the remainder is subtracted first to round down
	const int32 ScaledPenalty = OwnBaseValue * GunslingerStat_HalvedByEffect::PenaltyMultiplierNumerator;
	return (ScaledPenalty - (GunslingerStat_HalvedByEffect::PenaltyMultiplierDenominator - 1))
		/ GunslingerStat_HalvedByEffect::PenaltyMultiplierDenominator;
}

bool FGunslingerStat_HalvedByEffect::IsSet() const
{
	return *this != EmptyData;
}
