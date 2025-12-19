// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CutsceneProject : ModuleRules
{
	public CutsceneProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"MovieScene",
			"LevelSequence",
			"Sequencer",
			"MovieSceneTools",
			"LevelSequence",
			"Slate",
			"SlateCore",
			"EditorStyle"
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"LevelSequence",
			"UMG",
			"Slate",
			"SlateCore",
			"MovieScene",
			"MovieSceneTracks"
		});
		
		PrivateIncludePaths.AddRange(new string[] { "CutsceneProject" });
	}
}
