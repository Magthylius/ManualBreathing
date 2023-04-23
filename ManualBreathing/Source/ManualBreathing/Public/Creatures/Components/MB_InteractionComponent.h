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

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	float InteractionRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "01 Settings", meta = (AllowPrivateAccess))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueries;
};
