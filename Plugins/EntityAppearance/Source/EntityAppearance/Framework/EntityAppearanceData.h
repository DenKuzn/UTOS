// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableRenderAsset.h"

#include "EntityAppearanceData.generated.h"

/** «Внешность» of one entity: stored in the appearance facet under the entity's ID.
 *  The visual part of an entity lives here; its fields are added when the game is filled with content. */
USTRUCT()
struct ENTITYAPPEARANCE_API FEntityAppearanceData
{
	GENERATED_BODY()

// ============================================================
// Fields
// ============================================================
public:
	/** «модель» — may be absent; logic never reads it. Static or skeletal mesh.
	 *  Without it the runtime draws the entity with the engine's default primitive. */
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
	TSoftObjectPtr<UStaticMesh> Model = nullptr;

// ============================================================
// EmptyData & Validation
// ============================================================

	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FEntityAppearanceData EmptyData;

	/** Default comparison operator, primarily for comparing with EmptyData. */
	bool operator==(const FEntityAppearanceData& ComparedEntityAppearanceEntry) const = default;

	/** Returns false if the current struct equals EmptyData.
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;
};
