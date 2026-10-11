// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "Debug/DebugUTOSOverlaySubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"

#include "AssertUtils/Assert.h"

#include "Debug/SDebugUTOSDataAssetList.h"

namespace DebugUTOSOverlay
{
	// above ordinary game UI, which UMG adds at Z-order 0 and up
	constexpr int32 ViewportZOrder = 1000;
}

bool UDebugUTOSOverlaySubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	// gameplay worlds only: the editor's own world and preview worlds have no gameplay to start
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UDebugUTOSOverlaySubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// no local viewport (dedicated server) — nothing to show on, not an error
	UGameViewportClient* const GameViewport = InWorld.GetGameViewport();
	if (GameViewport == nullptr)
	{
		return;
	}

	const UGameInstance* const GameInstance = InWorld.GetGameInstance();
	assertUObjectPointerIsValid_return(GameInstance);

	// collected now, not at Initialize: the game instance subsystems are initialized and loaded by world BeginPlay
	OverlayWidget = SNew(SDebugUTOSDataAssetList).GameInstance(GameInstance);
	GameViewport->AddViewportWidgetContent(OverlayWidget.ToSharedRef(), DebugUTOSOverlay::ViewportZOrder);
	OverlayViewport = GameViewport;
}

void UDebugUTOSOverlaySubsystem::Deinitialize()
{
	if (OverlayWidget.IsValid())
	{
		UGameViewportClient* const GameViewport = OverlayViewport.Get();
		if (GameViewport != nullptr)
		{
			GameViewport->RemoveViewportWidgetContent(OverlayWidget.ToSharedRef());
		}

		OverlayWidget.Reset();
		OverlayViewport.Reset();
	}

	Super::Deinitialize();
}
