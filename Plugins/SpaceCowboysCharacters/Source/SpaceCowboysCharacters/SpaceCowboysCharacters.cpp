// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#include "SpaceCowboysCharacters.h"

#include "Modules/ModuleManager.h"

#include "Framework/GunslingerDataAsset.h"

void FSpaceCowboysCharactersModule::StartupModule()
{
	// the DAs are loaded and their IDs registered once the engine has started — not here, the engine is not initialized yet
	UEntityDataAsset_Base::RegisterAllIDsOfClassOnNativeTagsAdding(UGunslingerDataAsset::StaticClass());
}

IMPLEMENT_MODULE(FSpaceCowboysCharactersModule, SpaceCowboysCharacters)
