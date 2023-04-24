// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MB_InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANUALBREATHING_API UMB_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMB_InteractionComponent();

	void Interact();
	void SetupInteractionDetector(UShapeComponent* DetectorShape);

protected:
	UFUNCTION()
	void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	float InteractionRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueries;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TObjectPtr<UShapeComponent> InteractionDetector;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "02 Runtime Data", meta = (AllowPrivateAccess))
	TArray<TObjectPtr<AActor>> InteractablesInRange;
};
