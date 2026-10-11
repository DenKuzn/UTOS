// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Data/GunslingerStat.h"

#include "GunslingerStat_ScaledByStat.generated.h"

struct FGunslingerData;

/** A gunslinger stat that grows with another stat of the same gunslinger.
 *  While the evaluated value of the scaling stat is greater than 2, half of it (rounded down) is added to the own base value.
 *  The scaling stat is read by its evaluated value under the same current effects — it may change at runtime (a wound, a buff).
 *  A stat scaled by itself is asserted; a cycle through two formula stats is not guarded and recurses forever. */
USTRUCT()
struct SPACECOWBOYSCHARACTERS_API FGunslingerStat_ScaledByStat : public FGunslingerStat
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
	/** The stat whose evaluated value scales this one: one of the Gunslinger.Stats.* tags declared in FNGT_GunslingerTags. */
	UPROPERTY(EditDefaultsOnly, Category = "Stat", meta = (Categories = "Gunslinger.Stats"))
	FGameplayTag ScalingStat;

// ============================================================
// EmptyData & Validation
// ============================================================
public:
	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FGunslingerStat_ScaledByStat EmptyData;

	/** Default comparison operator, primarily for comparing with EmptyData. */
	bool operator==(const FGunslingerStat_ScaledByStat& ComparedGunslingerStat) const = default;

	/** Returns false if the current struct equals EmptyData.
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;
};
