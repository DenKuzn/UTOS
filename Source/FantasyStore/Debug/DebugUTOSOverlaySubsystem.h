// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "DebugUTOSOverlaySubsystem.generated.h"

class SWidget;
class UGameViewportClient;

/** DEBUG: shows the UTOS DataAsset list (SDebugUTOSDataAssetList) on the game viewport when gameplay starts.
 *  A world subsystem of game and PIE worlds: OnWorldBeginPlay is the first moment a world has both its game instance
 *  (whose subsystems — the UTOS ones included — initialized in UGameInstance::Init, before any world) and its viewport.
 *  The widget is built per world and removed from the viewport with it, so a map change rebuilds the list.
 *  Worlds without a local viewport (dedicated server) show nothing. Exists in every build configuration, Shipping included. */
UCLASS()
class FANTASYSTORE_API UDebugUTOSOverlaySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

// ============================================================
// Overridden Functions & Constructors
// ============================================================
protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

// ============================================================
// Class Fields
// ============================================================
private:
	/** The viewport the overlay was added to; weak — the viewport client outlives or dies with the world on its own terms. */
	UPROPERTY()
	TWeakObjectPtr<UGameViewportClient> OverlayViewport = nullptr;

	/** The overlay widget while it is on the viewport. Not a UPROPERTY: a Slate shared pointer. */
	TSharedPtr<SWidget> OverlayWidget = nullptr;
};
