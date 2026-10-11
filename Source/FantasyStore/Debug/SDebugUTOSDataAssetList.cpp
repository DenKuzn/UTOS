// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Debug/SDebugUTOSDataAssetList.h"

#include "Algo/Sort.h"
#include "Engine/DataAsset.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "AssertUtils/Assert.h"

#include "Framework/Entity/EntityDataAsset_Base.h"
#include "Framework/Entity/EntitySubsystem_Base.h"
#include "Framework/Facet/FacetSubsystem_Base.h"

namespace DebugUTOSDataAssetList
{
	// sizes are Slate units; at 1080p the DPI scale is 1.0, so the rows read as ~19 px text
	constexpr int32 TitleFontSize = 18;
	constexpr int32 RowFontSize = 14;

	const FLinearColor TitleColor(1.0f, 0.82f, 0.25f);
	const FLinearColor ColumnHeaderColor(0.65f, 0.65f, 0.65f);
	const FLinearColor SubsystemColor(0.45f, 0.85f, 1.0f);
	const FLinearColor DataAssetColor(1.0f, 1.0f, 1.0f);
	const FLinearColor TagIDColor(0.55f, 1.0f, 0.55f);
	const FLinearColor MutedColor(0.6f, 0.6f, 0.6f);
}

void SDebugUTOSDataAssetList::AddCell(const TSharedRef<SGridPanel>& Grid,
                                      const int32 Column,
                                      const int32 Row,
                                      const FString& Text,
                                      const FSlateFontInfo& Font,
                                      const FLinearColor& Color)
{
	Grid->AddSlot(Column, Row)
	.Padding(FMargin(0.0f, 2.0f, 28.0f, 2.0f))
	[
		SNew(STextBlock)
		.Text(FText::FromString(Text))
		.Font(Font)
		.ColorAndOpacity(Color)
	];
}

void SDebugUTOSDataAssetList::AddSubsystemRows(const TSharedRef<SGridPanel>& Grid,
                                               const USubsystem& Subsystem,
                                               const FString& Kind,
                                               const TArray<const UPrimaryDataAsset*>& DataAssets,
                                               int32& InOut_RowIndex)
{
	using namespace DebugUTOSDataAssetList;

	const FSlateFontInfo RowFont = FCoreStyle::GetDefaultFontStyle("Regular", RowFontSize);
	const FString SubsystemName = Subsystem.GetClass()->GetName();

	// a subsystem that loaded nothing still gets a row: "0 DataAssets" is the finding, not a missing subsystem
	if (DataAssets.IsEmpty())
	{
		AddCell(Grid, 0, InOut_RowIndex, SubsystemName, RowFont, SubsystemColor);
		AddCell(Grid, 1, InOut_RowIndex, Kind, RowFont, MutedColor);
		AddCell(Grid, 2, InOut_RowIndex, TEXT("(0 DataAssets loaded)"), RowFont, MutedColor);
		++InOut_RowIndex;
		return;
	}

	TArray<const UPrimaryDataAsset*> SortedDataAssets;
	SortedDataAssets.Reserve(DataAssets.Num());
	for (const UPrimaryDataAsset* const DataAsset : DataAssets)
	{
		assertUObjectPointerIsValid_withContinue(DataAsset);

		SortedDataAssets.Add(DataAsset);
	}

	Algo::SortBy(SortedDataAssets, [](const UPrimaryDataAsset* const DataAsset) { return DataAsset->GetName(); });

	for (const UPrimaryDataAsset* const DataAsset : SortedDataAssets)
	{
		AddCell(Grid, 0, InOut_RowIndex, SubsystemName, RowFont, SubsystemColor);
		AddCell(Grid, 1, InOut_RowIndex, Kind, RowFont, MutedColor);
		AddCell(Grid, 2, InOut_RowIndex, DataAsset->GetName(), RowFont, DataAssetColor);
		AddCell(Grid, 3, InOut_RowIndex, DataAsset->GetClass()->GetName(), RowFont, MutedColor);
		AddCell(Grid, 4, InOut_RowIndex, GetDataAssetTagIDString(*DataAsset), RowFont, TagIDColor);
		++InOut_RowIndex;
	}
}

FString SDebugUTOSDataAssetList::GetDataAssetTagIDString(const UPrimaryDataAsset& DataAsset)
{
	// only entity DataAssets carry a DA tag ID; a facet is keyed by the IDs of entity subsystems
	const UEntityDataAsset_Base* const EntityDataAsset = Cast<UEntityDataAsset_Base>(&DataAsset);
	if (EntityDataAsset == nullptr)
	{
		return TEXT("-");
	}

	const FGameplayTag AssetTagID = EntityDataAsset->GetAssetTagID();
	return AssetTagID.IsValid() ? AssetTagID.ToString() : TEXT("(tag ID not registered)");
}

void SDebugUTOSDataAssetList::Construct(const FArguments& InArgs)
{
	using namespace DebugUTOSDataAssetList;

	// an overlay: never steals clicks or focus from the game
	SetVisibility(EVisibility::HitTestInvisible);

	const UGameInstance* const GameInstance = InArgs._GameInstance;
	assertUObjectPointerIsValid_return(GameInstance);

	TArray<UEntitySubsystem_Base*> EntitySubsystems = GameInstance->GetSubsystemArrayCopy<UEntitySubsystem_Base>();
	TArray<UFacetSubsystem_Base*> FacetSubsystems = GameInstance->GetSubsystemArrayCopy<UFacetSubsystem_Base>();

	const auto ByClassName = [](const USubsystem* const Subsystem) { return Subsystem != nullptr ? Subsystem->GetClass()->GetName() : FString(); };
	Algo::SortBy(EntitySubsystems, ByClassName);
	Algo::SortBy(FacetSubsystems, ByClassName);

	const FSlateFontInfo ColumnHeaderFont = FCoreStyle::GetDefaultFontStyle("Bold", RowFontSize);
	const TSharedRef<SGridPanel> Grid = SNew(SGridPanel);

	int32 RowIndex = 0;
	AddCell(Grid, 0, RowIndex, TEXT("Subsystem"), ColumnHeaderFont, ColumnHeaderColor);
	AddCell(Grid, 1, RowIndex, TEXT("Kind"), ColumnHeaderFont, ColumnHeaderColor);
	AddCell(Grid, 2, RowIndex, TEXT("DataAsset"), ColumnHeaderFont, ColumnHeaderColor);
	AddCell(Grid, 3, RowIndex, TEXT("DataAsset class"), ColumnHeaderFont, ColumnHeaderColor);
	AddCell(Grid, 4, RowIndex, TEXT("DA tag ID"), ColumnHeaderFont, ColumnHeaderColor);
	++RowIndex;

	int32 SubsystemCount = 0;
	int32 DataAssetCount = 0;

	for (const UEntitySubsystem_Base* const Subsystem : EntitySubsystems)
	{
		assertUObjectPointerIsValid_withContinue(Subsystem);

		const TArray<const UPrimaryDataAsset*> DataAssets = Subsystem->DEBUG_GetLoadedDataAssets();
		AddSubsystemRows(Grid, *Subsystem, TEXT("Entity"), DataAssets, RowIndex);
		++SubsystemCount;
		DataAssetCount += DataAssets.Num();
	}

	for (const UFacetSubsystem_Base* const Subsystem : FacetSubsystems)
	{
		assertUObjectPointerIsValid_withContinue(Subsystem);

		const TArray<const UPrimaryDataAsset*> DataAssets = Subsystem->DEBUG_GetLoadedDataAssets();
		AddSubsystemRows(Grid, *Subsystem, TEXT("Facet"), DataAssets, RowIndex);
		++SubsystemCount;
		DataAssetCount += DataAssets.Num();
	}

	const FString Title = FString::Printf(TEXT("DEBUG  |  UTOS loaded DataAssets: %d subsystem(s), %d DataAsset(s)"),
	                                      SubsystemCount, DataAssetCount);

	ChildSlot
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Top)
	.Padding(FMargin(24.0f))
	[
		SNew(SBorder)
		.BorderImage(&BackgroundBrush)
		.Padding(FMargin(16.0f, 12.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0.0f, 0.0f, 0.0f, 8.0f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(Title))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", TitleFontSize))
				.ColorAndOpacity(TitleColor)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				Grid
			]
		]
	];
}
