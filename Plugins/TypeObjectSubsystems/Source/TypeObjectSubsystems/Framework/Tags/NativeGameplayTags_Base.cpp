// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Tags/NativeGameplayTags_Base.h"

#include "AssertUtils/Assert.h"
#include "GameplayTagsManager.h"

const FNativeGameplayTags_Base FNativeGameplayTags_Base::EmptyData{};

bool FNativeGameplayTags_Base::IsSet() const
{
	// identity, not value: the base declares no fields, so the defaulted operator== finds every tag struct equal to EmptyData
	return this != &EmptyData;
}

UScriptStruct* FNativeGameplayTags_Base::GetScriptStruct() const
{
	return StaticStruct();
}

void FNativeGameplayTags_Base::AddGameplayTagsByField()
{
	UScriptStruct* OwnerStruct = GetScriptStruct();
	assertUObjectPointerIsValid_return(OwnerStruct);

	for (TFieldIterator<FProperty> PropertyIterator(OwnerStruct); PropertyIterator; ++PropertyIterator)
	{
		FProperty* CurrentProperty = *PropertyIterator;
		assertIsNotNull_withContinue(CurrentProperty);

		// not every field is a tag: other fields are skipped
		FStructProperty* StructProperty = CastField<FStructProperty>(CurrentProperty);
		if (StructProperty == nullptr)
		{
			continue;
		}

		if (StructProperty->Struct != FGameplayTag::StaticStruct())
		{
			continue;
		}

		FGameplayTag& TagFieldRef = *(StructProperty->ContainerPtrToValuePtr<FGameplayTag>(this));

#if WITH_EDITOR
		const FString ToolTipText = StructProperty->GetToolTipText(false).ToString();
#else
		const FString ToolTipText = TEXT("");
#endif

		AddTag(TagFieldRef, CurrentProperty->GetName(), ToolTipText);
	}
}

FGameplayTag FNativeGameplayTags_Base::GetRootTag() const
{
	assertDefaultImplementationIsOverriden_return(FGameplayTag::EmptyTag);
}

void FNativeGameplayTags_Base::RegisterTags() const
{
	assertDefaultImplementationIsOverriden_return();
}

void FNativeGameplayTags_Base::AddTag(FGameplayTag& OutTag, FString StringTagName, const FString& TagComment)
{
	assertStringIsNotEmpty_return(StringTagName);

	StringTagName = StringTagName.Replace(TEXT("_"), TEXT("."));
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(StringTagName), FString(TEXT("(Native) " + TagComment)));
	assertGameplayTagIsValid_return(OutTag);
}
