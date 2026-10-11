// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FantasyStore : ModuleRules
{
	public FantasyStore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		// includes are written from the module root: "Framework/Sites/SitePlacementRules.h"
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "TypeObjectSubsystems" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AssertUtils" });

		// Slate: the debug overlay (Debug/SDebugUTOSDataAssetList) is built in C++ Slate, no UMG asset
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
