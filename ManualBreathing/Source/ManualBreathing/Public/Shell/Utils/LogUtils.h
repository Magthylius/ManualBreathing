// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMBCore, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogMBCreatures, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogMBWorld, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogMBShell, Display, All);

/**
 * 
 */
class FLogUtils
{
public:
    static wchar_t const* FromBool(const bool bInBoolean) { return bInBoolean ? TEXT("True") : TEXT("False"); }
	static void PrintScreen(const FString& InMessage, const FColor InColor = FColor::Cyan, const float InTime = 10.f, const int InKey = -1);
};
