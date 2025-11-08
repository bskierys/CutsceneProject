// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CutsceneProject : ModuleRules
{
	public CutsceneProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "LevelSequence" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"LevelSequence"
		});
		
		PrivateIncludePaths.AddRange(new string[] { "CutsceneProject" });
	}
}
