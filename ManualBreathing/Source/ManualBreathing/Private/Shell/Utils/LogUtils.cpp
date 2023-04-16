// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell/Utils/LogUtils.h"

DEFINE_LOG_CATEGORY(LogMBCore);
DEFINE_LOG_CATEGORY(LogMBCreatures);
DEFINE_LOG_CATEGORY(LogMBWorld);
DEFINE_LOG_CATEGORY(LogMBShell);

void FLogUtils::PrintScreen(const FString& InMessage, const FColor InColor, const float InTime, const int InKey)
{
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(InKey, InTime, InColor, InMessage);
	}
}
