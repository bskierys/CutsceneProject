#include "SubtitleSectionDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Subtitles/MovieSceneSubtitleSection.h"
#include "Subtitles/SubtitleColorPreset.h"
#include "Subtitles/SubtitleSubsystem.h"
#include "Subtitles/SubtitleSubsystemConfig.h"

TSharedRef<IDetailCustomization> FSubtitleSectionDetails::MakeInstance()
{
	return MakeShared<FSubtitleSectionDetails>();
}

void FSubtitleSectionDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	ColorIdProperty = DetailBuilder.GetProperty(
		GET_MEMBER_NAME_CHECKED(
			UMovieSceneSubtitleSection,
			SubtitleColorId
		)
	);

	DetailBuilder.HideProperty(ColorIdProperty);
	RefreshOptions();

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Subtitle");
	Category.AddCustomRow(FText::FromString("Subtitle Color")).NameContent()
		[
			ColorIdProperty->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(200.f)
		[
			SNew(SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&ColorOptions)
			.OnGenerateWidget_Lambda([](TSharedPtr<FName> Item)
			{
				return SNew(STextBlock)
					.Text(FText::FromName(*Item));
			})
			.IsEnabled_Lambda([this]()
			{
				return ColorOptions.Num() > 0;
			})
			.OnSelectionChanged_Lambda(
				[this](TSharedPtr<FName> NewValue, ESelectInfo::Type)
				{
					if (NewValue.IsValid())
					{
						ColorIdProperty->SetValue(*NewValue);
					}
				}
			)
			[
				SNew(STextBlock)
				.Text_Lambda([this]()
				{
					FName Current;
					ColorIdProperty->GetValue(Current);
					return FText::FromName(Current);
				})
			]
		];
}

void FSubtitleSectionDetails::RefreshOptions()
{
	ColorOptions.Reset();

	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequencer Editor Details: Can't get Editor World"));
		return;
	}

	USubtitleSubsystem* Subsystem = World->GetSubsystem<USubtitleSubsystem>();
	if (!IsValid(Subsystem) || !IsValid(Subsystem->Config))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequencer Editor Details: Can't get Subsystem Config"));
		return;
	}
	
	if (USubtitleColorPreset* Preset = Subsystem->Config->ColorPreset)
	{
		for (const FSubtitleColorEntry& Entry : Preset->Colors)
		{
			ColorOptions.Add(MakeShared<FName>(Entry.Id));
		}
	}
}
