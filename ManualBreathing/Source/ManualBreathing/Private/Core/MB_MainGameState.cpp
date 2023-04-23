// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainGameState.h"

#include "Core/MB_MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "World/MB_EarthActor.h"
#include "World/MB_ExplosionFieldSystem.h"

void AMB_MainGameState::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHabitat();

	APlayerController* PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (AMB_MainHUD* MainHUD = PlayerController->GetHUD<AMB_MainHUD>(); IsValid(MainHUD))
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetShowMouseCursor(true);
		
		UMB_MainMenuWidget* MainMenuWidget = MainHUD->SetMainMenuWidget(true);
		MainMenuWidget->StartGameEvent.AddLambda([this, PlayerController, MainHUD]()
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->SetShowMouseCursor(false);
			MainHUD->SetMainMenuWidget(false);
			MainHUD->SetHelmetWidget(true);

			AMB_AstronautCharacter* AstronautCharacter = Cast<AMB_AstronautCharacter>(PlayerController->GetCharacter());
			if (IsValid(AstronautCharacter))
			{
				AstronautCharacter->SetAllowBreathing(true);
			}

			//! Blow up the earth!
			AMB_EarthActor* EarthActor = Cast<AMB_EarthActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMB_EarthActor::StaticClass()));
			if (IsValid(EarthActor))
			{
				EarthActor->SetHidden(true);
			}

			const AMB_ExplosionFieldSystem* ExplosionField = Cast<AMB_ExplosionFieldSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), AMB_ExplosionFieldSystem::StaticClass()));
			if (IsValid(ExplosionField))
			{
				ExplosionField->CreateExplosion();
			}
		});
	}
}

void AMB_MainGameState::SetupHabitat()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), HabitatActorClass, PotentialHabitats);
	
	if (PotentialHabitats.Num() > 0)
	{
		const int RandomIndex = FMath::RandRange(0, PotentialHabitats.Num() -1 );
		TrueHabitat = Cast<AMB_HabitatActor>(PotentialHabitats[RandomIndex]);
		TrueHabitat->ActivateHabitat();
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("AMB_MainGameState: No habitats found!"));
}
