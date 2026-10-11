// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectDescriptionSubsystem.h"

#include "AssertUtils/Assert.h"

#include "ObjectDescriptionDataAsset.h"


DEFINE_LOG_CATEGORY_STATIC( LogObjectDescriptionPlugin, Log, All );

TSubclassOf<UFacetDataAsset_Base> UObjectDescriptionSubsystem::GetDataAssetClass() const
{
	return UObjectDescriptionDataAsset::StaticClass();
}

const FObjectDescription& UObjectDescriptionSubsystem::GetObjectDescription(const FGameplayTag& ObjectTag) const
{
	assertGameplayTagIsValid_return( ObjectTag, FObjectDescription::EmptyData );

	// the DA of the tag's root (one DA per entity subsystem)
	const UFacetDataAsset_Base* const DataAsset = FindDataAssetById( ObjectTag );
	assertUObjectPointerIsValid_return( DataAsset, FObjectDescription::EmptyData );

	// the base keys only GetDataAssetClass instances
	return CastChecked<UObjectDescriptionDataAsset>( DataAsset )->FindObjectDescription( ObjectTag );
}

