#include "SubtitleSection.h"
#include "SequencerSectionPainter.h"
#include "Rendering/DrawElements.h"
#include "EditorStyleSet.h"
#include "Subtitles/MovieSceneSubtitleSection.h"
#include "Subtitles/SubtitleSubsystem.h"

FSubtitleSection::FSubtitleSection(UMovieSceneSection& InSection): SectionObject(InSection)
{
}

int32 FSubtitleSection::OnPaintSection(FSequencerSectionPainter& InPainter) const
{
	const UMovieSceneSubtitleSection* SubtitleSection =
		Cast<UMovieSceneSubtitleSection>(&SectionObject);

	FLinearColor Tint = FLinearColor::White;
	if (UWorld* World = GEditor->GetEditorWorldContext().World())
	{
		if (USubtitleSubsystem* Subsystem = World->GetSubsystem<USubtitleSubsystem>())
		{
			Tint = Subsystem->ResolveColor(SubtitleSection->SubtitleColorId);
		}
	}

	int32 LayerId = InPainter.PaintSectionBackground(Tint.CopyWithNewOpacity(0.15f * InPainter.GhostAlpha));

	return LayerId;
}

FText FSubtitleSection::GetSectionTitle() const
{
	const UMovieSceneSubtitleSection* Sub =
		Cast<UMovieSceneSubtitleSection>(&SectionObject);

	if (!Sub)
	{
		return FText::FromString(TEXT("Subtitle"));
	}

	const FString Speaker = Sub->Speaker.ToString();
	const FString TextPreview = Sub->SubtitleText.ToString();
	const FString SubtitlePreview =
		FString::Printf(TEXT("%s: %s"), *Speaker, *TextPreview);

	constexpr int32 MaxLen = 60;

	if (SubtitlePreview.Len() <= MaxLen)
	{
		return FText::FromString(SubtitlePreview);
	}

	const FString Truncated =
		SubtitlePreview.Left(MaxLen) + TEXT("…");

	return FText::FromString(Truncated);
}

FText FSubtitleSection::GetSectionToolTip() const
{
	const UMovieSceneSubtitleSection* Sub =
		Cast<UMovieSceneSubtitleSection>(&SectionObject);

	if (!Sub)
	{
		return FText::GetEmpty();
	}

	return FText::Format(
		FText::FromString("{0}: {1}"),
		Sub->Speaker,
		Sub->SubtitleText
	);
}
