#pragma once

#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class USubtitleColorPreset;

class FSubtitleSectionDetails : public IDetailCustomization
{
	
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(
		IDetailLayoutBuilder& DetailBuilder
	) override;

private:
	TArray<TSharedPtr<FName>> ColorOptions;
	TSharedPtr<IPropertyHandle> ColorIdProperty;

	void RefreshOptions();
};
