// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell/Utils/LogUtils.h"

DEFINE_LOG_CATEGORY(LogPKCore);
DEFINE_LOG_CATEGORY(LogPKPirates);
DEFINE_LOG_CATEGORY(LogPKWorld);
DEFINE_LOG_CATEGORY(LogPKShell);

void FLogUtils::PrintScreen(const FString& InMessage, const FColor InColor, const float InTime, const int InKey)
{
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(InKey, InTime, InColor, InMessage);
	}
}
