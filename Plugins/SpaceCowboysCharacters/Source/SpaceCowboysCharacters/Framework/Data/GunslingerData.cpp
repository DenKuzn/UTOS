// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Data/GunslingerData.h"

#include "AssertUtils/Assert.h"

const FGunslingerData FGunslingerData::EmptyData{};

bool FGunslingerData::operator==(const FGunslingerData& ComparedGunslingerData) const
{
	return Tier == ComparedGunslingerData.Tier
		&& Stats.OrderIndependentCompareEqual(ComparedGunslingerData.Stats)
		&& Archetype == ComparedGunslingerData.Archetype
		&& StartingPerks == ComparedGunslingerData.StartingPerks
		&& MetaTags == ComparedGunslingerData.MetaTags
		&& MovementAbility == ComparedGunslingerData.MovementAbility
		&& Abilities == ComparedGunslingerData.Abilities
		&& bAvailableInTavern == ComparedGunslingerData.bAvailableInTavern
		&& bCanBeDismissed == ComparedGunslingerData.bCanBeDismissed;
}

bool FGunslingerData::IsSet() const
{
	return *this != EmptyData;
}

const FGunslingerStat& FGunslingerData::GetStat(const FGameplayTag& StatTag) const
{
	assertGameplayTagIsValid_return(StatTag, FGunslingerStat::EmptyData);

	const TInstancedStruct<FGunslingerStat>* const InstancedStat = Stats.Find(StatTag);
	assertIsNotNull_return(InstancedStat, FGunslingerStat::EmptyData);

	const FGunslingerStat* const Stat = InstancedStat->GetPtr();
	assertIsNotNull_return(Stat, FGunslingerStat::EmptyData);

	return *Stat;
}
