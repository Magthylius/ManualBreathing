// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/MB_AstronautCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Shell/Utils/LogUtils.h"

/* --- PUBLIC ---*/

AMB_AstronautCharacter::AMB_AstronautCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMesh->SetupAttachment(CameraComponent);
	FirstPersonMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
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

	OxygenAmount = 100.f;
}

void AMB_AstronautCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//! If both are the same held down, hold breath
	BreatheMode = bIsInhaling && bIsExhaling || !bIsInhaling && !bIsExhaling ? EMB_BreatheMode::Holding : bIsInhaling ? EMB_BreatheMode::Inhaling : EMB_BreatheMode::Exhaling;
	
	if (BreatheMode != EMB_BreatheMode::Holding)
	{
		const bool bCurrentlyInhaling = BreatheMode == EMB_BreatheMode::Inhaling;
		
		BreatheRate = LungMaxAirCapacity / FullBreathingTime * DeltaTime;
		LungAirAmount = FMath::Clamp(LungAirAmount + (bCurrentlyInhaling ? BreatheRate : -BreatheRate), 0.f, LungMaxAirCapacity);
		if (LungAirAmount < LungMaxAirCapacity) OxygenAmount += bCurrentlyInhaling ? BreatheRate : 0.f; 
	}

	OxygenAmount -= IdleOxygenBurnRate * DeltaTime;
	OxygenAmount = FMath::Clamp(OxygenAmount, 0.f, 100.f);
	
	FLogUtils::PrintScreen(FString("Breathe Mode: ") + UEnum::GetValueAsString(BreatheMode), FColor::Cyan, DeltaTime);
	FLogUtils::PrintScreen(FString("Lung Air Amount: ") + FString::SanitizeFloat(LungAirAmount), FColor::Red, DeltaTime);
	FLogUtils::PrintScreen(FString("Oxygen Amount: ") + FString::SanitizeFloat(OxygenAmount), FColor::Yellow, DeltaTime);
}

void AMB_AstronautCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMB_AstronautCharacter::PerformLook);
		
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

void AMB_AstronautCharacter::PerformInhale(const FInputActionValue& Value)
{
	const bool bIsPressed = Value.Get<bool>();
	bIsInhaling = bIsPressed;
}

void AMB_AstronautCharacter::PerformExhale(const FInputActionValue& Value)
{
	const bool bIsPressed = Value.Get<bool>();
	bIsExhaling = bIsPressed;
}
