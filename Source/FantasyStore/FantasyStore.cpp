// Copyright Epic Games, Inc. All Rights Reserved.

#include "FantasyStore.h"


void FFantasyStoreModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FFantasyStoreModule, FantasyStore, "FantasyStore");
