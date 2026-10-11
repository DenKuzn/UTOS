// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/** The game module: registers the project's native tags (FFantasyStoreTags). */
class FFantasyStoreModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
};
