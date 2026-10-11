// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"

#include "Framework/Data/GunslingerStat.h"

#include "GunslingerData.generated.h"

/** Description of one gunslinger — a mercenary hired in the saloon.
 *  Holds no race and no ID: the race is the DataAsset the description sits in,
 *  the ID is the description's key in that asset's map, Gunslinger.<AssetName>.<Index>. */
USTRUCT()
struct SPACECOWBOYSCHARACTERS_API FGunslingerData
{
	GENERATED_BODY()

// ============================================================
// Fields
// ============================================================
public:
	/** One of the Gunslinger.Tier.* tags declared in FNGT_GunslingerTags. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger", meta = (Categories = "Gunslinger.Tier"))
	FGameplayTag Tier;

	/** Stat key (one of the Gunslinger.Stats.* tags declared in FNGT_GunslingerTags) → the stat; the chosen struct type sets the stat's formula.
	 *  A stat is read through GetStat, its current value through FGunslingerStat::GetEvaluatedStat. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger", meta = (Categories = "Gunslinger.Stats"))
	TMap<FGameplayTag, TInstancedStruct<FGunslingerStat>> Stats;

	/** One of the Gunslinger.Archetype.* tags declared in FNGT_GunslingerTags. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger", meta = (Categories = "Gunslinger.Archetype"))
	FGameplayTag Archetype;

	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	FGameplayTagContainer StartingPerks;

	/** Archetype marks (mechanical / organic / insect) effects filter their targets by. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	FGameplayTagContainer MetaTags;

	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	FGameplayTag MovementAbility;

	/** Innate activatable body abilities. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	FGameplayTagContainer Abilities;

	/** False — never offered in the saloon; the gunslinger is obtained outside it. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	bool bAvailableInTavern = true;

	/** False — a story character that cannot be dismissed from the gang. */
	UPROPERTY(EditDefaultsOnly, Category = "Gunslinger")
	bool bCanBeDismissed = true;

// ============================================================
// EmptyData & Validation
// ============================================================

	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FGunslingerData EmptyData;

	/** Comparison operator, primarily for comparing with EmptyData. Explicit because TMap deletes its operator==. */
	bool operator==(const FGunslingerData& ComparedGunslingerData) const;

	/** Returns false if the current struct equals EmptyData.
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the stat of the gunslinger; FGunslingerStat::EmptyData with an assert when the gunslinger has no such stat.
	 * @param StatTag The stat key, one of the Gunslinger.Stats.* tags.
	 */
	const FGunslingerStat& GetStat(const FGameplayTag& StatTag) const;
};
