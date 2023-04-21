// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MB_HelmetWidget.h"
#include "Kismet/GameplayStatics.h"

void UMB_HelmetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AstronautCharacter))
	{
		AstronautCharacter = Cast<AMB_AstronautCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!IsValid(AstronautCharacter))
		{
			UE_LOG(LogTemp, Error, TEXT("UMB_HelmetWidget: Invalid astronaut character!"));
			return;
		}
	}
	
	const FString HeartRateText = FString::Format(TEXT("HEART RATE: {0}"), {FMath::RoundToInt(AstronautCharacter->GetHeartRate())});
	const FString BreathRateText = FString::Format(TEXT("BREATH RATE: {0} per minute"), {FMath::RoundToInt(AstronautCharacter->GetBreathingRate())});
	const FString LungCapacityText = FString::Format(TEXT("LUNG CAPACITY: {0}%"), {FMath::RoundToInt(AstronautCharacter->GetLungAirAmountNormalized() * 100.f)});
	HeartRateTextBlock->SetText(FText::FromString(HeartRateText));
	BreathRateTextBlock->SetText(FText::FromString(BreathRateText));
	LungCapacityTextBlock->SetText(FText::FromString(LungCapacityText));

	UE_LOG(LogTemp, Warning, TEXT("UMB_HelmetWidget: BR: %s"), *BreathRateText);


	const float OxygenAmount = AstronautCharacter->GetOxygenAmountNormalized();
	FString OxygenLevel;
	if (OxygenAmount > 0.8f) OxygenLevel = "HIGH";
	else if (OxygenAmount > 0.5f) OxygenLevel = "REGULAR";
	else if (OxygenAmount > 0.3f) OxygenLevel = "LOW";
	else if (OxygenAmount > 0.01f) OxygenLevel = "CRITICAL";
	else OxygenLevel = "DANGER";
	const FString OxygenLevelText = FString("OXYGEN LEVEL: ") + OxygenLevel;
	OxygenDisplayTextBlock->SetText(FText::FromString(OxygenLevelText));
}
