// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

/** Hosts the gunslinger classes. At start-up it schedules the registration of every gunslinger ID as a native gameplay tag;
 *  the tags struct registers itself at module load. */
class FSpaceCowboysCharactersModule : public IModuleInterface
{
// ============================================================
// Overridden Functions & Constructors
// ============================================================
public:
	virtual void StartupModule() override;
};
