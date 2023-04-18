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
enum class EMB_BreatheMode
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
	AMB_AstronautCharacter();
	
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TEnumAsByte<EMB_BreatheMode> BreatheMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bIsInhaling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bIsExhaling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float LungAirAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float HeartRate;
};
