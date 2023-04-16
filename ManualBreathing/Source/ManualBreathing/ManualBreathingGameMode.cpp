// Copyright Epic Games, Inc. All Rights Reserved.

#include "ManualBreathingGameMode.h"
#include "ManualBreathingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AManualBreathingGameMode::AManualBreathingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
