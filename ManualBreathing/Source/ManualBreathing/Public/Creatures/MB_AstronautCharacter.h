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
	
public:
	AMB_AstronautCharacter(const FObjectInitializer& ObjectInitializer);
	
	void ForceLowOxy(bool bResetDeathTimeLeft = true);
	void ForceLowOxy(float DeathTimeLeft);

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
	float DefaultHeartRate = 60.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float DefaultBreathingRate = 15.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float FullBreathingTime = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float IdleOxygenBurnRate = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float MovingOxygenBurnRate = 15.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay", meta = (AllowPrivateAccess))
	float JumpingOxygenBurnRate = 25.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyDeathGap = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	float LowOxyDeathResetGap = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	FVector2D LowOxyFocalDistanceRange = FVector2D(1.f, 50.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings | Gameplay | Low Oxygen", meta = (AllowPrivateAccess))
	FVector2D LowOxyVignetteIntensityRange = FVector2D(0.4f, 1.f);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TEnumAsByte<EMB_BreatheMode> BreatheMode;
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
	TArray<float> BreathTimeStamps;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float OxygenAmount = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float HeartRate = 60.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float BreathingRate = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float LowOxyDeathTimeLeft = 30.f;
};
