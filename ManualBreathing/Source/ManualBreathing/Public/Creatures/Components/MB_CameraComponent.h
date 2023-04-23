// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "MB_CameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class MANUALBREATHING_API UMB_CameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	void SetTargetFieldOfField(const float InTargetFOV);

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	float FieldOfViewSpeed = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	bool bFieldOfViewDirty = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	float TargetFieldOfView = -1.f;
};
