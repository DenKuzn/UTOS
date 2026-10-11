// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GunslingerStat.generated.h"

struct FGameplayTagContainer;
struct FGunslingerData;

/** One stat of a gunslinger: the base value set in the DataAsset and the formula that turns it into the current stat.
 *  The base formula returns the base value as is; a derived struct overrides GetEvaluatedStat with its own formula,
 *  which may depend on the gunslinger's other stats and on the effects currently on the gunslinger.
 *  The current stat is read only through GetEvaluatedStat — the base value has no public getter.
 *  Held polymorphically in FGunslingerData::Stats, keyed by a Gunslinger.Stats.* tag. */
USTRUCT()
struct SPACECOWBOYSCHARACTERS_API FGunslingerStat
{
	GENERATED_BODY()

// ============================================================
// Constructors
// ============================================================
public:
	virtual ~FGunslingerStat();

// ============================================================
// Fields
// ============================================================
private:
	/** Base value of the stat. May be negative; the default (the lowest int32) marks "not entered". */
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 BaseValue = TNumericLimits<int32>::Lowest();

// ============================================================
// EmptyData & Validation
// ============================================================
public:
	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FGunslingerStat EmptyData;

	/** Default comparison operator, primarily for comparing with EmptyData. */
	bool operator==(const FGunslingerStat& ComparedGunslingerStat) const = default;

	/** Returns false if the current struct equals EmptyData.
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;

// ============================================================
// Protected Functions
// ============================================================
protected:
	/** Current value of a stat whose base value was never entered: a zero stat neither adds nor takes away. */
	static constexpr int32 UnsetStatValue = 0;

	/**
	 * Returns this stat's own base value — for a derived formula that starts from it.
	 * Other stats are read only through their GetEvaluatedStat.
	 */
	int32 GetBaseValue() const;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns the current value of the stat — the only way to read it. The base formula returns the base value;
	 * every formula returns UnsetStatValue for a stat whose base value was never entered.
	 * @param GunslingerData The gunslinger that owns the stat; a formula reads the gunslinger's other stats from it.
	 * @param CurrentEffectsOnGunslinger The effects currently on the gunslinger; a formula may change the stat by them
	 *        and passes the same container on when it evaluates another stat.
	 */
	virtual int32 GetEvaluatedStat(const FGunslingerData& GunslingerData,
	                               const FGameplayTagContainer& CurrentEffectsOnGunslinger) const;
};
