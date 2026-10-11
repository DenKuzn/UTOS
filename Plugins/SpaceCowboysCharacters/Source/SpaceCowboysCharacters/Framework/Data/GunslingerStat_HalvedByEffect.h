// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Data/GunslingerStat.h"

#include "GunslingerStat_HalvedByEffect.generated.h"

struct FGunslingerData;

/** A gunslinger stat that an effect on the gunslinger weakens.
 *  While the current effects hold the halving effect (or a child of it): a positive base value is halved, rounded toward zero;
 *  a negative base value (a penalty) is multiplied by 1.5, rounded away from zero, so it only gets stronger (-5 → -8);
 *  a zero base value stays zero. Without the effect the stat is its own base value. */
USTRUCT()
struct SPACECOWBOYSCHARACTERS_API FGunslingerStat_HalvedByEffect : public FGunslingerStat
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
	virtual int32 GetEvaluatedStat(const FGunslingerData& GunslingerData,
	                               const FGameplayTagContainer& CurrentEffectsOnGunslinger) const override;

// ============================================================
// Fields
// ============================================================
private:
	/** The effect that halves this stat (or strengthens its penalty): one of the Gunslinger.Effects.* tags declared in FNGT_GunslingerTags. */
	UPROPERTY(EditDefaultsOnly, Category = "Stat", meta = (Categories = "Gunslinger.Effects"))
	FGameplayTag HalvingEffect;

// ============================================================
// EmptyData & Validation
// ============================================================
public:
	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FGunslingerStat_HalvedByEffect EmptyData;

	/** Default comparison operator, primarily for comparing with EmptyData. */
	bool operator==(const FGunslingerStat_HalvedByEffect& ComparedGunslingerStat) const = default;

	/** Returns false if the current struct equals EmptyData.
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;
};
