// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyGameEditor : ModuleRules
{
	public MyGameEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        // Type = ModuleType.Editor;

        PrivateDependencyModuleNames.AddRange(new string[]
        {
	        "CutsceneProject",
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "Sequencer",
            "MovieScene",
            "MovieSceneTools",
            "LevelSequence",
            "Slate",
            "SlateCore",
            "InputCore",
            "EditorStyle"
        });
        
        PrivateIncludePaths.AddRange(new string[] { "CutsceneProject", "MyGameEditor" });
	}
}
