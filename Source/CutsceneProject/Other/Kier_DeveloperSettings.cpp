// Created by Bartłomiej Kierys


#include "Other/Kier_DeveloperSettings.h"
#include "SubsystemConfig.h"

USubsystemConfig* UKier_DeveloperSettings::GetSubsystemConfigByClass(TSubclassOf<USubsystemConfig> ParamClass) const
{
	if (!ParamClass)
	{ 
		return nullptr;
	}

	for (const TSoftObjectPtr<USubsystemConfig>& ConfigRef : SubsystemConfig)
	{
		if (ConfigRef.IsNull()) 
			continue;

		if (USubsystemConfig* LoadedConfig = ConfigRef.LoadSynchronous())
		{
			if (LoadedConfig->IsA(ParamClass)) 
			{
				return LoadedConfig;
			}
		}
	}
	return nullptr;
}
