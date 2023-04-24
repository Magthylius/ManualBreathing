// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MB_MainGameState.h"
#include "Core/MB_MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Shell/Utils/LogUtils.h"
#include "World/MB_EarthActor.h"
#include "World/MB_ExplosionFieldSystem.h"

/* --- PROTECTED ---*/

void AMB_MainGameState::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHabitat();

	APlayerController* PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	
	const AMB_AstronautCharacter* AstronautCharacter = Cast<AMB_AstronautCharacter>(PlayerController->GetCharacter());
	AstronautCharacter->GetCameraComponent()->SetFieldOfView(60.f);
	
	AMB_MainHUD* MainHUD = PlayerController->GetHUD<AMB_MainHUD>();
	UMB_MainMenuWidget* MainMenuWidget = MainHUD->SetMainMenuWidget(true);
	MainMenuWidget->StartGameEvent.AddUObject(this, &AMB_MainGameState::StartGameInternal);
}

void AMB_MainGameState::StartGameInternal()
{
	APlayerController* PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMB_AstronautCharacter* AstronautCharacter = Cast<AMB_AstronautCharacter>(PlayerController->GetCharacter());
	AMB_MainHUD* MainHUD = PlayerController->GetHUD<AMB_MainHUD>();
	
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);

	AstronautCharacter->SetPostProcessing(true);
	AstronautCharacter->SetAllowBreathing(true);
	AstronautCharacter->GetCameraComponent()->SetTargetFieldOfField(90.f);

	UMB_MainMenuWidget* MainMenuWidget = MainHUD->SetMainMenuWidget(false);
	MainHUD->SetHelmetWidget(true);

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

	MainMenuWidget->StartGameEvent.RemoveAll(this);
}

void AMB_MainGameState::EndGameInternal()
{
	FLogUtils::PrintScreen("Game has ended! You win!");
	AMB_AstronautCharacter* AstronautCharacter = Cast<AMB_AstronautCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AstronautCharacter->SetAllowBreathing(false);
}

/* --- PRIVATE ---*/

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
