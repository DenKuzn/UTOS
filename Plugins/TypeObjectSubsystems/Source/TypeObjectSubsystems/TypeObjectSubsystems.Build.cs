// Copyright Denis Kuznetsov (DenKuzn). All Rights Reserved.

using UnrealBuildTool;

public class TypeObjectSubsystems : ModuleRules
{
	public TypeObjectSubsystems(ReadOnlyTargetRules Target) : base(Target)
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
				"AssertUtils"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetRegistry"
			}
			);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");

			// the rename of an entity DataAsset checks out DefaultGameplayTags.ini before writing tag redirects into it
			PrivateDependencyModuleNames.Add("SourceControl");
		}
	}
}
