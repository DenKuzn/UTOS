// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

using UnrealBuildTool;

public class SpaceCowboysCharacters : ModuleRules
{
	public SpaceCowboysCharacters(ReadOnlyTargetRules Target) : base(Target)
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

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssertUtils"
			}
			);
	}
}
