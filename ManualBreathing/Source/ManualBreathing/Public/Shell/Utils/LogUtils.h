// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPKCore, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPKPirates, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPKWorld, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(LogPKShell, Display, All);

/**
 * 
 */
class FLogUtils
{
public:
    static wchar_t const* FromBool(const bool bInBoolean) { return bInBoolean ? TEXT("True") : TEXT("False"); }
	static void PrintScreen(const FString& InMessage, const FColor InColor = FColor::Cyan, const float InTime = 10.f, const int InKey = -1);
};
