// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Brushes/SlateColorBrush.h"
#include "Widgets/SCompoundWidget.h"

class SGridPanel;
class UGameInstance;
class UPrimaryDataAsset;
class USubsystem;

/** DEBUG overlay: lists every DataAsset loaded by every UTOS subsystem (entity and facet) of a game instance.
 *  Collects once, at Construct, through the DEBUG_GetLoadedDataAssets accessors of the UTOS bases; the game instance
 *  is not kept. One table row per DataAsset: subsystem class, kind, DataAsset name, DataAsset class, DA tag ID
 *  (entity DataAssets only); a subsystem with no DataAssets gets one row that says so. Ignores input. */
class FANTASYSTORE_API SDebugUTOSDataAssetList : public SCompoundWidget
{
// ============================================================
// Class Fields
// ============================================================
private:
	FSlateColorBrush BackgroundBrush{FLinearColor(0.0f, 0.0f, 0.0f, 0.78f)};

// ============================================================
// Private Functions
// ============================================================
private:
	static void AddCell(const TSharedRef<SGridPanel>& Grid,
	                    const int32 Column,
	                    const int32 Row,
	                    const FString& Text,
	                    const FSlateFontInfo& Font,
	                    const FLinearColor& Color);

	static void AddSubsystemRows(const TSharedRef<SGridPanel>& Grid,
	                             const USubsystem& Subsystem,
	                             const FString& Kind,
	                             const TArray<const UPrimaryDataAsset*>& DataAssets,
	                             int32& InOut_RowIndex);

	static FString GetDataAssetTagIDString(const UPrimaryDataAsset& DataAsset);

// ============================================================
// Public Interface
// ============================================================
public:
	SLATE_BEGIN_ARGS(SDebugUTOSDataAssetList)
		: _GameInstance(nullptr)
		{}
		/** The game instance whose UTOS subsystems are listed; read during Construct only. */
		SLATE_ARGUMENT(const UGameInstance*, GameInstance)
	SLATE_END_ARGS()

	/**
	 * Collects the DataAssets of every UTOS subsystem of the game instance and builds the table.
	 * @param InArgs Slate arguments; GameInstance must be valid.
	 */
	void Construct(const FArguments& InArgs);
};
