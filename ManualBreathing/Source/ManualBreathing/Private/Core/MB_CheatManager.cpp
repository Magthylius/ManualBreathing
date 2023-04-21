// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_CheatManager.h"
#include "Creatures/MB_AstronautCharacter.h"

void UMB_CheatManager::LowOxyReset(const bool bResetDeathTimeLeft /* true */) const
{
	if (AMB_AstronautCharacter* Astronaut = Cast<AMB_AstronautCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); IsValid(Astronaut))
	{
		Astronaut->ForceLowOxy(bResetDeathTimeLeft);
	}
}

void UMB_CheatManager::LowOxy(const float DeathTimeLeft) const
{
	if (AMB_AstronautCharacter* Astronaut = Cast<AMB_AstronautCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); IsValid(Astronaut))
	{
		Astronaut->ForceLowOxy(DeathTimeLeft);
	}
}

void UMB_CheatManager::GodMode(const bool bEnable /* true */) const
{
	if (AMB_AstronautCharacter* Astronaut = Cast<AMB_AstronautCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); IsValid(Astronaut))
	{
		Astronaut->EnableGodMode(bEnable);
	}
}

void UMB_CheatManager::PrintStats() const
{
	if (AMB_AstronautCharacter* Astronaut = Cast<AMB_AstronautCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()); IsValid(Astronaut))
	{
		Astronaut->TogglePrintStats();
	}
}
