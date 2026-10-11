// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Tags/NativeGameplayTags_Base.h"

#include "NGT_GunslingerTags.generated.h"

/** Native gameplay tags of the gunslinger subsystem: the root, the tier values, the archetype values, the stat keys and the effects.
 *  Every gunslinger DataAsset tag ID (Gunslinger.<AssetName>) and every gunslinger ID (Gunslinger.<AssetName>.<Index>)
 *  is composed under the root. Underscores in a field name become dots in the tag.
 *  The tags register themselves when the module loads. */
USTRUCT()
struct SPACECOWBOYSCHARACTERS_API FNGT_GunslingerTags : public FNativeGameplayTags_Base
{
	GENERATED_BODY()
	UTOS_NATIVE_TAGS_BODY(FNGT_GunslingerTags);

// ============================================================
// Fields
// ============================================================
public:
	/** Root of the gunslinger subsystem: every gunslinger DataAsset tag ID and gunslinger ID lives under it. */
	UPROPERTY()
	FGameplayTag Gunslinger;

	/** Parent of the gunslinger tiers: rarity and progression from the free starter to the legend. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier;

	/** Tier ★ — free or nearly free. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier_Starter;

	/** Tier ★★ — the gang's standard. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier_Common;

	/** Tier ★★★ — solid. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier_Solid;

	/** Tier ★★★★ — rare. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier_Rare;

	/** Tier ★★★★★ — taken from bosses. */
	UPROPERTY()
	FGameplayTag Gunslinger_Tier_Legendary;

	/** Parent of the gunslinger archetypes: the style hint of which weapon a gunslinger is born for. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype;

	/** Long-range shooter. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype_Sharpshooter;

	/** Daredevil. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype_Daredevil;

	/** Tank. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype_Tank;

	/** Slippery. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype_Slippery;

	/** Beast bruiser — the only archetype of the robot dog. */
	UPROPERTY()
	FGameplayTag Gunslinger_Archetype_BeastBruiser;

	/** Parent of the gunslinger stats: every key of FGunslingerData::Stats lives under it. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats;

	/** Stat key: vitality. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats_Vitality;

	/** Stat key: aim. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats_Aim;

	/** Stat key: mobility. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats_Mobility;

	/** Stat key: evasion. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats_Evasion;

	/** Stat key: initiative. */
	UPROPERTY()
	FGameplayTag Gunslinger_Stats_Initiative;

	/** Parent of the effects on a gunslinger: the tags a stat formula reads from the current effects container. */
	UPROPERTY()
	FGameplayTag Gunslinger_Effects;

	/** Test effect: halves a stat built on FGunslingerStat_HalvedByEffect. */
	UPROPERTY()
	FGameplayTag Gunslinger_Effects_Test;
};
