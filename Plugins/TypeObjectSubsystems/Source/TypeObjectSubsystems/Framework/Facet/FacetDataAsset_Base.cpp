// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Facet/FacetDataAsset_Base.h"

#include "AssertUtils/Assert.h"

#if WITH_EDITOR
void UFacetDataAsset_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	TArray<FGameplayTag> Ids;
	CollectIds(Ids);

	// a single key has nothing to disagree with; the check reports a mismatch itself
	FindCommonRootName(Ids);
}
#endif

FName UFacetDataAsset_Base::FindCommonRootName(const TArray<FGameplayTag>& Ids)
{
	FName CommonRootName = NAME_None;
	for (const FGameplayTag& Id : Ids)
	{
		// an element just added in the editor has no key yet
		if (!Id.IsValid())
		{
			continue;
		}

		const FName RootName = GetRootNameOf(Id, FNAME_Add);
		assertNameIsAssigned_return(RootName, NAME_None);

		if (CommonRootName.IsNone())
		{
			CommonRootName = RootName;
			continue;
		}

		assertIsTrue_return(RootName == CommonRootName, NAME_None);
	}

	return CommonRootName;
}

FName UFacetDataAsset_Base::GetRootNameOf(const FGameplayTag& Id, const EFindName FindType)
{
	TStringBuilder<128> IdName;
	Id.GetTagName().ToString(IdName);

	const FStringView IdView = IdName.ToView();
	int32 DotIndex = INDEX_NONE;
	const bool bHasParent = IdView.FindChar(TEXT('.'), DotIndex);

	return FName(bHasParent ? IdView.Left(DotIndex) : IdView, FindType);
}

FName UFacetDataAsset_Base::GetRootName() const
{
	TArray<FGameplayTag> Ids;
	CollectIds(Ids);

	return FindCommonRootName(Ids);
}
