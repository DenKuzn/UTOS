// Copyright by Denis Kuznetsov. 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ObjectDescriptionStruct.generated.h"

/** Base Struct for Objects Description like Items, Weapons, Abilities, etc.
 *  Lightweight data container holding localized name, descriptions,
 *  and an optional image reference for any describable game object. */
USTRUCT( BlueprintType )
struct OBJECTDESCRIPTIONPLUGIN_API FObjectDescription
{
	GENERATED_BODY()

// ============================================================
// Constructors
// ============================================================
public:
	FObjectDescription();

// ============================================================
// Fields
// ============================================================
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText MainName = FText::FromString( "Default Name" );

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText ShortDescription = FText::FromString( "Default Short Description" );

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText FullDescription = FText::FromString( "Default Full Description" );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSoftObjectPtr<UTexture2D> Image = nullptr;

// ============================================================
// EmptyData & Validation
// ============================================================

	/** Empty struct instance used for returning by reference in case of logic errors. */
	static const FObjectDescription EmptyData;

	/** Comparison operator. Explicit because FText does not support defaulted operator==. */
	bool operator==( const FObjectDescription& ComparedObjectDescription ) const;

	/** Returns false if MainName is empty or equals the default "Default Name".
	 *  Name is fixed — assertion macros expect this function on custom structs. */
	bool IsSet() const;
};
