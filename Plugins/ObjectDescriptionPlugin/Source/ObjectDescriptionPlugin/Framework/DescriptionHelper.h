// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "AssertUtils/Assert.h"
#include "Framework/ObjectDescriptionSubsystem.h"
#include "Framework/ObjectDescriptionStruct.h"

namespace DescriptionHelper
{
	/** Resolves item display name via ObjectDescriptionSubsystem.
	 *  Falls back to Tag.ToString() if description not found. */
	inline FText GetItemName(const UWorld* World, const FGameplayTag& ItemTag)
	{
		const FText Fallback = FText::FromString(ItemTag.ToString());

		assertUObjectPointerIsValid_return(World, Fallback);
		assertGameplayTagIsValid_return(ItemTag, Fallback);

		const UGameInstance* const GI = World->GetGameInstance();
		assertUObjectPointerIsValid_return(GI, Fallback);

		const UObjectDescriptionSubsystem* const DescSub = GI->GetSubsystem<UObjectDescriptionSubsystem>();
		assertUObjectPointerIsValid_return(DescSub, Fallback);

		const FObjectDescription& Desc = DescSub->GetObjectDescription(ItemTag);
		assertCustomStructIsSet_return(Desc, Fallback);

		return Desc.MainName;
	}

	/** Resolves item short description via ObjectDescriptionSubsystem.
	 *  Returns empty FText if description not found or not set. */
	inline FText GetItemShortDescription(const UWorld* World, const FGameplayTag& ItemTag)
	{
		assertUObjectPointerIsValid_return(World, FText::GetEmpty());
		assertGameplayTagIsValid_return(ItemTag, FText::GetEmpty());

		const UGameInstance* const GI = World->GetGameInstance();
		assertUObjectPointerIsValid_return(GI, FText::GetEmpty());

		const UObjectDescriptionSubsystem* const DescSub = GI->GetSubsystem<UObjectDescriptionSubsystem>();
		assertUObjectPointerIsValid_return(DescSub, FText::GetEmpty());

		const FObjectDescription& Desc = DescSub->GetObjectDescription(ItemTag);
		assertCustomStructIsSet_return(Desc, FText::GetEmpty());

		return Desc.ShortDescription;
	}
}
