// Copyright by Denis Kuznetsov. 2023. All Rights Reserved.

#include "Framework/AssetManager/EnhancedAssetManager.h"

#include "AssetRegistry/IAssetRegistry.h"

#include "AssertUtils/Assert.h"

UEnhancedAssetManager* UEnhancedAssetManager::Get()
{
	assertIsNotNull_return(GEngine, nullptr);

	UEnhancedAssetManager* const This = Cast<UEnhancedAssetManager>( GEngine->AssetManager );
	assertUObjectPointerIsValid_return(This, nullptr);

	return This;
}

void UEnhancedAssetManager::LoadSyncAllAssetsByClass(const UClass* AssetClass,
                                                     TArray<UObject*>& OUT AssetArray)
{
	assertUObjectPointerIsValid_return(AssetClass);

	IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();

#if WITH_EDITOR
	// in the editor the registry gathers asynchronously at startup — an unfinished scan would miss assets
	if (AssetRegistry.IsLoadingAssets())
	{
		AssetRegistry.WaitForCompletion();
	}
#endif

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssetsByClass(AssetClass->GetClassPathName(), AssetDataList, /*bSearchSubClasses*/ true);

	UE_LOG(LogEnhancedAssetManager, Log, TEXT("%s(). Found %i assets of class %s"), *FString(__FUNCTION__), AssetDataList.Num(), *AssetClass->GetName());

	AssetArray.Reserve(AssetArray.Num() + AssetDataList.Num());
	for (const FAssetData& AssetData : AssetDataList)
	{
		const FSoftObjectPtr SoftObjectPtr = FSoftObjectPtr(AssetData.GetSoftObjectPath());
		UObject* const LoadedAsset = SoftObjectPtr.LoadSynchronous();

		assertUObjectPointerIsValid_withContinue(LoadedAsset);

		UE_LOG(LogEnhancedAssetManager, Log, TEXT("%s(). Object Loaded. %s"), *FString(__FUNCTION__), *LoadedAsset->GetFName().ToString());
		AssetArray.Add(LoadedAsset);
	}
}
