// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainGameState.h"

#include "Core/MB_MainHUD.h"
#include "Kismet/GameplayStatics.h"

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
		MainMenuWidget->StartGameEvent.AddLambda([PlayerController, MainHUD]()
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->SetShowMouseCursor(false);
			MainHUD->SetMainMenuWidget(false);
			MainHUD->SetHelmetWidget(true);

			//! Blow up the earth!
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
