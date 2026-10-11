// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectDescriptionDataAsset.h"

#include "AssertUtils/Assert.h"

void UObjectDescriptionDataAsset::CollectIds(TArray<FGameplayTag>& Out_Ids) const
{
	ObjectDescriptions.GenerateKeyArray(Out_Ids);
}

bool UObjectDescriptionDataAsset::ContainsId(const FGameplayTag& Id) const
{
	return ObjectDescriptions.Contains(Id);
}

const FObjectDescription& UObjectDescriptionDataAsset::FindObjectDescription(const FGameplayTag& Id) const
{
	assertGameplayTagIsValid_return(Id, FObjectDescription::EmptyData);

	const FObjectDescription* const ObjectDescription = ObjectDescriptions.Find(Id);
	assertIsNotNull_return(ObjectDescription, FObjectDescription::EmptyData);

	return *ObjectDescription;
}
