// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Framework/Facet/FacetSubsystem_Base.h"

#include "Framework/EntityAppearanceData.h"

#include "EntityAppearanceSubsystem.generated.h"

/** Facet subsystem «Внешность»: how any visible entity looks, keyed by the ID of the entity,
 *  whatever subsystem owns it. Self-contained: no other system knows it, and it knows no other system.
 *  The place of the game's visual part: its fields and data rules are added when the game is filled with content.
 *  An entity without an entry is valid — the runtime draws it with the engine's default primitive.
 *  The base loads every UEntityAppearanceDataAsset at Initialize. */
UCLASS()
class ENTITYAPPEARANCE_API UEntityAppearanceSubsystem : public UFacetSubsystem_Base
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
protected:
	virtual TSubclassOf<UFacetDataAsset_Base> GetDataAssetClass() const override;

// ============================================================
// Public Interface
// ============================================================
public:
	/**
	 * Returns true if the entity has an appearance entry. No assert: a caller may ask about any entity.
	 * @param Id The entity ID of any entity subsystem.
	 */
	bool HasAppearance(const FGameplayTag& Id) const;

	/**
	 * Returns the appearance of the entity; EmptyData with an ensure when the entity has no entry — ask HasAppearance first.
	 * @param Id The entity ID of any entity subsystem.
	 */
	const FEntityAppearanceData& GetAppearance(const FGameplayTag& Id) const;
};
