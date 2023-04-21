// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MB_AstronautCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UENUM()
enum class EMB_BreatheMode : uint8
{
	Holding,
	Inhaling,
	Exhaling
};

UCLASS()
class MANUALBREATHING_API AMB_AstronautCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class UMB_CheatManager;
	
public:
	AMB_AstronautCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	
	void PerformMove(const FInputActionValue& Value);
	void PerformLook(const FInputActionValue& Value);

	void PerformInhale(const FInputActionValue& Value);
	void PerformExhale(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta= (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta= (AllowPrivateAccess))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta= (AllowPrivateAccess))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> InhaleAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> ExhaleAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float LungMaxAirCapacity = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float FullBreathingTime = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float IdleOxygenBurnRate = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float MovingOxygenBurnRate = 7.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float JumpingOxygenBurnRate = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float IntakeToOxygenRatio = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float DefaultOxygenTankAmount = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	FVector2D HeartRateRange = FVector2D(60.f, 150.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	TObjectPtr<UCurveFloat> HeartRateChangeCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float HeartRateChangeMultiplier = 0.04f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float HeartMaxOxyBurnMultiplier = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	FVector2D BreathingRateRange = FVector2D(28.f, 75.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyDeathGap = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyDeathRecoveryGap = 10.f; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyMinWalkSpeed = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	FVector2D LowOxyFocalDistanceRange = FVector2D(1.f, 50.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	FVector2D LowOxyVignetteIntensityRange = FVector2D(0.4f, 1.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	FVector2D LowOxySceneFringeIntensityRange = FVector2D(0.f, 3.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyEffectSpeed = 1.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	EMB_BreatheMode BreatheMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bIsInhaling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bIsExhaling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bExpectingExhale = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float AirIntakeRate = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float LungAirAmount = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float BreathAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float OxygenTankAmount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cache", meta = (AllowPrivateAccess))
	float DefaultWalkSpeed = 600.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cache", meta = (AllowPrivateAccess))
	float OxygenAmount = 5000.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cache", meta = (AllowPrivateAccess))
	float HeartRate = 60.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cache", meta = (AllowPrivateAccess))
	float TargetHeartRate = 60.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cache", meta = (AllowPrivateAccess))
	float BreathingRate = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Counters", meta = (AllowPrivateAccess))
	float LowOxyDeathTimeLeft = 30.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Counters", meta = (AllowPrivateAccess))
	float TargetEffectAlpha = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Counters", meta = (AllowPrivateAccess))
	float CurrentEffectAlpha = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Counters", meta = (AllowPrivateAccess))
	bool bWasPreviouslyLowOxygen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Counters", meta = (AllowPrivateAccess))
	float LowOxyRecoverTimeStamp = -1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data | Cheats", meta = (AllowPrivateAccess))
	bool bIsGodMode = false;

	void ForceLowOxy(const bool bResetDeathTimeLeft = true);
	void ForceLowOxy(const float DeathTimeLeft);
	void EnableGodMode(const bool bEnable = true);
};
