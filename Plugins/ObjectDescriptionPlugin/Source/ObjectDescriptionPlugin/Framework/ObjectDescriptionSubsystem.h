// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ObjectDescriptionStruct.h"
#include "Framework/Facet/FacetSubsystem_Base.h"
#include "ObjectDescriptionSubsystem.generated.h"

/** Text facet subsystem: the base loads every UObjectDescriptionDataAsset at Initialize,
 *  so object names or descriptions can be retrieved at any point in the code by tag. */
UCLASS()
class OBJECTDESCRIPTIONPLUGIN_API UObjectDescriptionSubsystem : public UFacetSubsystem_Base
{
	GENERATED_BODY()

protected:

	virtual TSubclassOf<UFacetDataAsset_Base> GetDataAssetClass() const override;

public:

	const FObjectDescription& GetObjectDescription(const FGameplayTag& ObjectTag) const;


};
