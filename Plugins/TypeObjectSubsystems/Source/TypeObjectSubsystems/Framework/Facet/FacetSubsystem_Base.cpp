// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Framework/Facet/FacetSubsystem_Base.h"

#include "AssertUtils/Assert.h"

#include "Framework/AssetManager/EnhancedAssetManager.h"
#include "Framework/Facet/FacetDataAsset_Base.h"

TArray<const UPrimaryDataAsset*> UFacetSubsystem_Base::DEBUG_GetLoadedDataAssets() const
{
	TArray<const UPrimaryDataAsset*> DataAssets;
	DataAssets.Reserve(DataAssetByRoot.Num());
	for (const TPair<FName, TObjectPtr<UFacetDataAsset_Base>>& RootEntry : DataAssetByRoot)
	{
		assertUObjectPointerIsValid_withContinue(RootEntry.Value);

		DataAssets.Add(RootEntry.Value.Get());
	}

	return DataAssets;
}

void UFacetSubsystem_Base::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const TSubclassOf<UFacetDataAsset_Base> DataAssetClass = GetDataAssetClass();
	assertUObjectPointerIsValid_return(DataAssetClass);

	TArray<UObject*> SynchronousLoadedAssets;
	UEnhancedAssetManager::LoadSyncAllAssetsByClass(DataAssetClass, SynchronousLoadedAssets);

	// no tag registration: a facet is keyed by the IDs of entity subsystems, it owns none
	for (UObject* const LoadedAsset : SynchronousLoadedAssets)
	{
		assertUObjectPointerIsValid_withContinue(LoadedAsset);
		assertIsTrue_withContinue(LoadedAsset->IsA(DataAssetClass));

		AddDataAsset(CastChecked<UFacetDataAsset_Base>(LoadedAsset));
	}
}

void UFacetSubsystem_Base::AddDataAsset(UFacetDataAsset_Base* DataAsset)
{
	assertUObjectPointerIsValid_return(DataAsset);

	const FName RootName = DataAsset->GetRootName();
	assertNameIsAssigned_return(RootName);

	assertIsNull_return(DataAssetByRoot.Find(RootName));

	DataAssetByRoot.Add(RootName, DataAsset);
}

const UFacetDataAsset_Base* UFacetSubsystem_Base::FindDataAssetById(const FGameplayTag& Id) const
{
	assertGameplayTagIsValid_return(Id, nullptr);

	// FNAME_Find: a root unknown to the name table cannot be a key either
	const TObjectPtr<UFacetDataAsset_Base>* const DataAsset = DataAssetByRoot.Find(UFacetDataAsset_Base::GetRootNameOf(Id));
	assertIsNotNull_return(DataAsset, nullptr);
	assertUObjectPointerIsValid_return(*DataAsset, nullptr);

	return DataAsset->Get();
}

bool UFacetSubsystem_Base::ContainsId(const FGameplayTag& Id) const
{
	// a question, not a request: no DA for the root is a plain "no", so the map is read directly, not through FindDataAssetById
	const TObjectPtr<UFacetDataAsset_Base>* const DataAsset = DataAssetByRoot.Find(UFacetDataAsset_Base::GetRootNameOf(Id));
	if (DataAsset == nullptr)
	{
		return false;
	}

	assertUObjectPointerIsValid_return(*DataAsset, false);

	return (*DataAsset)->ContainsId(Id);
}
