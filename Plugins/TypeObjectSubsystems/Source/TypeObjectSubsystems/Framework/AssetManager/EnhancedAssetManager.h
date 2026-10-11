// Copyright by Denis Kuznetsov. 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Engine/AssetManagerSettings.h"

#include "AssertUtils/Assert.h"
#include "AssertUtils/DebugMacroses.h"

#include "EnhancedAssetManager.generated.h"

DEFINE_LOG_CATEGORY_STATIC( LogEnhancedAssetManager, Log, All );

/** Needed to use custom assets more flexibly in the editor.
 *
 */

UCLASS()
class TYPEOBJECTSUBSYSTEMS_API UEnhancedAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	/** Returns the engine's asset manager; nullptr when the engine has none or it is not a UEnhancedAssetManager. */
	static UEnhancedAssetManager* Get();

public:

	template <class Type>
	void AsyncLoadAsset(TSoftObjectPtr<Type> SoftObjectPtr,
						Type** Outer,
						FStreamableDelegate OnLoadedObjectDelegate,
						FString AssetNameForDebug = "UnknownAssetType")
	{
		assertIsNotNull_return( Outer );

		//OutHandle.Reset();
		//OutHandle = nullptr;

		if ( ::IsValid( SoftObjectPtr.Get() ) )
		{
			*Outer = Cast<Type>( SoftObjectPtr.Get() );
			UE_LOG(LogTemp, Error, TEXT("%s(). Object is already loaded. AssetName: %s."), *FString(__FUNCTION__), *AssetNameForDebug);
			OnLoadedObjectDelegate.ExecuteIfBound();
			return;
		}

		if ( SoftObjectPtr.IsPending() )
		{
			TSharedPtr<FStreamableHandle> NewStreambleHandle;
			FStreamableDelegate OnLoaded;
			OnLoaded.BindLambda( [this, &TempOutHandle = NewStreambleHandle, &Outer = *Outer, &OnLoadedObjectDelegate = OnLoadedObjectDelegate]()
			{
				HandleLoadedAsset( TempOutHandle, &Outer, OnLoadedObjectDelegate );
			} );
			UEnhancedAssetManager* const EnhancedAssetManager = Get();
			assertUObjectPointerIsValid_return( EnhancedAssetManager );

			NewStreambleHandle = EnhancedAssetManager->GetStreamableManager().RequestAsyncLoad( SoftObjectPtr.ToSoftObjectPath(), OnLoaded );
			return;
		}

		assertNeverReached_ignore();

		// the caller still waits for the delegate
		OnLoadedObjectDelegate.ExecuteIfBound();
	}


	template <typename AssetType>
	static void LoadAsyncPrimaryDataAssets(TDelegate<void(TArray<AssetType*>)> OnAssetsLoadedDelegate)
	{
		const FString AssetName = AssetType::StaticClass()->GetName();
		const FPrimaryAssetType DataAssetType = FPrimaryAssetType{AssetType::StaticClass()->GetFName()};

		UAssetManager::Get().LoadPrimaryAssetsWithType( DataAssetType,
		                                                TArray<FName>(),
		                                                FStreamableDelegate::CreateLambda( [OnAssetsLoadedDelegate, LambdaAssetName = AssetName]()
		                                                {
			                                                UAssetManager& AssetManager = UAssetManager::Get();
			                                                TArray<FAssetData> DataAssetNames;
			                                                AssetManager.GetPrimaryAssetDataList( FPrimaryAssetType{AssetType::StaticClass()->GetFName()}, DataAssetNames );

			                                                TArray<AssetType*> AssetArray;

			                                                if ( DataAssetNames.Num() == 0 )
			                                                {
				                                                UE_LOG( LogEnhancedAssetManager, Warning, TEXT("%s(). No DataAsset %s found"), *FString( __FUNCTION__ ), *LambdaAssetName );
				                                                OnAssetsLoadedDelegate.ExecuteIfBound( AssetArray );
				                                                return;
			                                                }

			                                                AssetArray.Reserve( DataAssetNames.Num() );

			                                                for ( const FAssetData& LoadedAssetDataName : DataAssetNames )
			                                                {
				                                                AssetType* const PrimaryDataAsset = Cast<AssetType>( AssetManager.GetPrimaryAssetObject( LoadedAssetDataName.GetPrimaryAssetId() ) );
				                                                assertUObjectPointerIsValid_withContinue( PrimaryDataAsset );
				                                                assertContainerDoesNotContainElement_withContinue( AssetArray, PrimaryDataAsset );

				                                                AssetArray.AddUnique( PrimaryDataAsset );
			                                                }

			                                                UE_LOG( LogEnhancedAssetManager, Log, TEXT("%s(). Loaded %d DataAsset type: %s."), *FString( __FUNCTION__ ), AssetArray.Num(), *LambdaAssetName );
			                                                OnAssetsLoadedDelegate.ExecuteIfBound( AssetArray );
		                                                } ),

		                                                FStreamableManager::AsyncLoadHighPriority );
	}


	/** Synchronously loads every asset of the class and of its subclasses, wherever it lies in the project.
	 *  The assets are found through the asset registry by class, not by scanning a path.
	 * @param AssetClass - Class of the assets to load. Can be any class inherited from UObject.
	 * @param AssetArray - Array the loaded assets are added to. */
	static void LoadSyncAllAssetsByClass(const UClass* AssetClass,
	                                     TArray<UObject*>& OUT AssetArray);

	/** Synchronous data loading + loads all child objects from AssetType. A typed wrapper over LoadSyncAllAssetsByClass.
	 * @tparam AssetType - Data type. Can be any class inherited from UObject.
	 * @param AssetArray - Array where data will be loaded. */
	template <typename AssetType>
	static void LoadSyncAllAssetsByType(TArray<AssetType*>& OUT AssetArray)
	{
		static_assert(TIsDerivedFrom<AssetType, UObject>::Value, "LoadSyncAllAssetsByType takes a class derived from UObject");

		TArray<UObject*> LoadedAssets;
		LoadSyncAllAssetsByClass(AssetType::StaticClass(), LoadedAssets);

		AssetArray.Reserve(AssetArray.Num() + LoadedAssets.Num());
		for (UObject* const LoadedAsset : LoadedAssets)
		{
			assertUObjectPointerIsValid_withContinue(LoadedAsset);

			AssetArray.Add(CastChecked<AssetType>(LoadedAsset));
		}
	}



private:

	template <class Type>
	void HandleLoadedAsset(TSharedPtr<FStreamableHandle>& StreamableHandle,
	                       Type** Outer,
	                       FStreamableDelegate OnLoadedObjectDelegate)
	{
		assertSmartPointerIsValid_return( StreamableHandle );
		assertIsNotNull_return( Outer );

		*Outer = Cast<Type>( StreamableHandle->GetLoadedAsset() );
		StreamableHandle.Reset();
		OnLoadedObjectDelegate.ExecuteIfBound();

		UE_LOG( LogTemp, Error, TEXT("%s(). Is Valid Bullet: %s"), *FString(__FUNCTION__), TEXT_TRUE_FALSE( ::IsValid( *Outer ) ) );
	}
};
