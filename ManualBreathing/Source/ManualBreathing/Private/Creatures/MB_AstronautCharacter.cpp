// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/MB_AstronautCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Shell/Utils/LogUtils.h"

/* --- PUBLIC ---*/

AMB_AstronautCharacter::AMB_AstronautCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	GetCharacterMovement()->SetWalkableFloorAngle(55.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 200.f;
	GetCharacterMovement()->GravityScale = 0.165f;
	GetCharacterMovement()->AirControl = 0.1f;

	CameraComponent = CreateDefaultSubobject<UMB_CameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;

	CameraComponent->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = 1;
	CameraComponent->PostProcessSettings.bOverride_VignetteIntensity = 1;
	CameraComponent->PostProcessSettings.bOverride_SceneFringeIntensity = 1;
	CameraComponent->PostProcessSettings.DepthOfFieldFocalDistance = LowOxyFocalDistanceRange.Y;
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMesh->SetupAttachment(CameraComponent);
	FirstPersonMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	InteractionComponent = CreateDefaultSubobject<UMB_InteractionComponent>("InteractionComponent");
}

/* --- PROTECTED ---*/

void AMB_AstronautCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	OxygenAmount = LungMaxAirCapacity;
	HeartRate = HeartRateRange.X;
	TargetHeartRate = HeartRate;
	BreathingRate = BreathingRateRange.X;
	OxygenTankAmount = DefaultOxygenTankAmount;

	LowOxyDeathTimeLeft = LowOxyDeathGap;
}

void AMB_AstronautCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bBreathingAllowed) return;
	
	const float WorldTimeSeconds = GetWorld()->TimeSeconds;
	
	//! If both are the same held down, hold breath
	BreatheMode = bIsInhaling && bIsExhaling || !bIsInhaling && !bIsExhaling ? EMB_BreatheMode::Holding : bIsInhaling ? EMB_BreatheMode::Inhaling : EMB_BreatheMode::Exhaling;
	
	if (BreatheMode != EMB_BreatheMode::Holding)
	{
		const bool bCurrentlyInhaling = BreatheMode == EMB_BreatheMode::Inhaling;
		
		AirIntakeRate = LungMaxAirCapacity / FullBreathingTime * DeltaTime;
		LungAirAmount = FMath::Clamp(LungAirAmount + (bCurrentlyInhaling ? AirIntakeRate : -AirIntakeRate), 0.f, LungMaxAirCapacity);
		
		if (bCurrentlyInhaling && LungAirAmount < LungMaxAirCapacity)
		{
			const float OxygenUptake = AirIntakeRate * IntakeToOxygenRatio; 
			OxygenAmount += OxygenUptake;
			OxygenTankAmount = FMath::Max(0.f, OxygenTankAmount - OxygenUptake);
		}
	}
	
	if (bIsGodMode) return;
	
	BreathingRate = BreathAmount / WorldTimeSeconds * 60.f;
	
	const float BreathingStep = UKismetMathLibrary::NormalizeToRange(BreathingRate, BreathingRateRange.X, BreathingRateRange.Y);
	
	TargetHeartRate = FMath::Lerp(HeartRateRange.X, HeartRateRange.Y, BreathingStep);
	HeartRate = FMath::Lerp(HeartRate, TargetHeartRate, HeartRateChangeMultiplier * DeltaTime);
	
	const float HeartRateStep = UKismetMathLibrary::NormalizeToRange(HeartRate, HeartRateRange.X, HeartRateRange.Y);
	const float IdleBurn = IdleOxygenBurnRate * FMath::Max(1.f, HeartMaxOxyBurnMultiplier * HeartRateStep);
	OxygenAmount = FMath::Clamp(OxygenAmount - IdleBurn * DeltaTime, 0.f, 100.f);

	const bool bLowOxygen = OxygenAmount <= 0.f;
	if (bLowOxygen)
	{
		LowOxyRecoverTimeStamp = WorldTimeSeconds + LowOxyDeathRecoveryGap;
		
		LowOxyDeathTimeLeft = FMath::Clamp(LowOxyDeathTimeLeft - DeltaTime, 0.f, LowOxyDeathGap);
		TargetEffectAlpha = LowOxyDeathTimeLeft / LowOxyDeathGap;
	}
	else if (LowOxyRecoverTimeStamp > 0.f && WorldTimeSeconds > LowOxyRecoverTimeStamp)
	{
		LowOxyDeathTimeLeft = LowOxyDeathGap;
		TargetEffectAlpha = 1.f;
		LowOxyRecoverTimeStamp = -1.f;
	}

	CurrentEffectAlpha = FMath::Lerp(CurrentEffectAlpha, TargetEffectAlpha, LowOxyEffectSpeed * DeltaTime);

	const float FocalDistance = FMath::Lerp(LowOxyFocalDistanceRange.X, LowOxyFocalDistanceRange.Y, CurrentEffectAlpha);
	const float VignetteIntensity = FMath::Lerp(LowOxyVignetteIntensityRange.Y, LowOxyVignetteIntensityRange.X, CurrentEffectAlpha);
	const float SceneFringeIntensity = FMath::Lerp(LowOxySceneFringeIntensityRange.Y, LowOxySceneFringeIntensityRange.X, CurrentEffectAlpha);

	CameraComponent->PostProcessSettings.DepthOfFieldFocalDistance = FocalDistance;
	CameraComponent->PostProcessSettings.VignetteIntensity = VignetteIntensity;
	CameraComponent->PostProcessSettings.SceneFringeIntensity = SceneFringeIntensity;

	const float CurrentSpeed = FMath::Lerp(LowOxyMinWalkSpeed, DefaultWalkSpeed, CurrentEffectAlpha);
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;

	if (!bPrintStats) return;

	FLogUtils::PrintScreen(FString("Breathe Mode: ") + UEnum::GetValueAsString(BreatheMode), FColor::Cyan, DeltaTime);
	FLogUtils::PrintScreen(FString("Lung Air Amount: ") + FString::SanitizeFloat(LungAirAmount), FColor::Red, DeltaTime);
	FLogUtils::PrintScreen(FString("Oxygen Amount: ") + FString::SanitizeFloat(OxygenAmount), FColor::Yellow, DeltaTime);
	FLogUtils::PrintScreen(FString("Breathing Rate: ") + FString::SanitizeFloat(BreathingRate) + FString(" per minute") , FColor::White, DeltaTime);
	FLogUtils::PrintScreen(FString("Heart Rate: ") + FString::SanitizeFloat(HeartRate), FColor::White, DeltaTime);
	FLogUtils::PrintScreen(FString("Oxygen Tank: ") + FString::SanitizeFloat(OxygenTankAmount), FColor::Blue, DeltaTime);
	if (bLowOxygen) FLogUtils::PrintScreen(FString("Low oxygen! Time left: ") + FString::SanitizeFloat(LowOxyDeathTimeLeft), FColor::Red, DeltaTime);
}

void AMB_AstronautCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformLook);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMB_AstronautCharacter::PerformInteraction);
		
		EnhancedInputComponent->BindAction(InhaleAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformInhale);
		EnhancedInputComponent->BindAction(InhaleAction, ETriggerEvent::Completed, this, &AMB_AstronautCharacter::PerformInhale);
		EnhancedInputComponent->BindAction(ExhaleAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformExhale);
		EnhancedInputComponent->BindAction(ExhaleAction, ETriggerEvent::Completed, this, &AMB_AstronautCharacter::PerformExhale);
	}
}

void AMB_AstronautCharacter::Jump()
{
	Super::Jump();
	OxygenAmount -= JumpingOxygenBurnRate * GetWorld()->DeltaTimeSeconds;
}

void AMB_AstronautCharacter::PerformMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		OxygenAmount -= MovingOxygenBurnRate * GetWorld()->DeltaTimeSeconds;
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMB_AstronautCharacter::PerformLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMB_AstronautCharacter::PerformInteraction(const FInputActionValue& Value)
{
	InteractionComponent->Interact();
}

void AMB_AstronautCharacter::PerformInhale(const FInputActionValue& Value)
{
	if (const bool bIsPressed = Value.Get<bool>(); bIsInhaling != bIsPressed)
	{
		bIsInhaling = bIsPressed;
		bExpectingExhale = true;
	}
}

void AMB_AstronautCharacter::PerformExhale(const FInputActionValue& Value)
{
	if (const bool bIsPressed = Value.Get<bool>(); bIsExhaling != bIsPressed)
	{
		bIsExhaling = bIsPressed;
		
		if (bExpectingExhale)
		{
			bExpectingExhale = false;
			BreathAmount++;
		}
	}
}

/* --- PRIVATE ---*/

void AMB_AstronautCharacter::ForceLowOxy(const bool bResetDeathTimeLeft /* true */)
{
	OxygenAmount = 0.f;
	
	if (bResetDeathTimeLeft)
	{
		LowOxyDeathTimeLeft = LowOxyDeathGap;
	}
}

void AMB_AstronautCharacter::ForceLowOxy(const float DeathTimeLeft)
{
	OxygenAmount = 0.f;
	LowOxyDeathTimeLeft = DeathTimeLeft;
}

void AMB_AstronautCharacter::EnableGodMode(const bool bEnable /* true */)
{
	bIsGodMode = bEnable;
}

void AMB_AstronautCharacter::TogglePrintStats()
{
	bPrintStats = !bPrintStats;
}
