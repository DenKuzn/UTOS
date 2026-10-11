// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

using UnrealBuildTool;

public class EntityAppearance : ModuleRules
{
	public EntityAppearance(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				ModuleDirectory
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"TypeObjectSubsystems"
			}
			);
	}
}
