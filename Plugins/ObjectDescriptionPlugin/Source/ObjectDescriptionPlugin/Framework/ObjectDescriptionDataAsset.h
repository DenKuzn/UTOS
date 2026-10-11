// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Framework/Facet/FacetDataAsset_Base.h"
#include "ObjectDescriptionStruct.h"
#include "ObjectDescriptionDataAsset.generated.h"


/** Text facet of objects: names, descriptions and an image, keyed by the exact object tag (an entity ID).
 *  Read only through UObjectDescriptionSubsystem. */
UCLASS()
class OBJECTDESCRIPTIONPLUGIN_API UObjectDescriptionDataAsset : public UFacetDataAsset_Base
{
	GENERATED_BODY()

public:

	virtual void CollectIds(TArray<FGameplayTag>& Out_Ids) const override;

	virtual bool ContainsId(const FGameplayTag& Id) const override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Object Description" , meta = (TitleProperty = "Key" ))
	TMap<FGameplayTag, FObjectDescription> ObjectDescriptions;


public:
	/**
	 * Returns the description held under the ID; EmptyData with an assert when this DA has no such ID.
	 * @param Id The object tag (an entity ID).
	 */
	const FObjectDescription& FindObjectDescription(const FGameplayTag& Id) const;
};
