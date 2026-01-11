// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyGameEditor.h"
// #include "SubtitleTrackEditor.h"

#include "ISequencerModule.h"
#include "Modules/ModuleManager.h"
#include "Stage/CutsceneCameraTrackEditor.h"
#include "Subtitles/SubtitleSectionDetails.h"
#include "Subtitles/SubtitleTrackEditor.h"

IMPLEMENT_MODULE(FMyGameEditorModule, MyGameEditor)

void FMyGameEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("MyGameEditor module loaded"));

	ISequencerModule& SequencerModule =
		FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer");

	SubtitleTrackEditorHandle = SequencerModule.RegisterTrackEditor(
		FOnCreateTrackEditor::CreateStatic(
			&FSubtitleTrackEditor::CreateTrackEditorInstance
		)
	);

	CutsceneCameraTrackHandle = SequencerModule.RegisterTrackEditor(
		FOnCreateTrackEditor::CreateStatic(
			&FCutsceneCameraTrackEditor::CreateTrackEditorInstance
		)
	);

	FPropertyEditorModule& PropertyModule =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(
		"MovieSceneSubtitleSection",
		FOnGetDetailCustomizationInstance::CreateStatic(
			&FSubtitleSectionDetails::MakeInstance
		)
	);
}

void FMyGameEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("Sequencer"))
	{
		ISequencerModule& SequencerModule = FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer");

		if (SubtitleTrackEditorHandle.IsValid())
		{
			SequencerModule.UnRegisterTrackEditor(SubtitleTrackEditorHandle);
		}

		if (CutsceneCameraTrackHandle.IsValid())
		{
			SequencerModule.UnRegisterTrackEditor(CutsceneCameraTrackHandle);
		}

		FPropertyEditorModule& PropertyModule =
			FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		PropertyModule.UnregisterCustomClassLayout("MovieSceneSubtitleSection");
	}
}
