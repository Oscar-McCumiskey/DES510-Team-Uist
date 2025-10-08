// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/ShockMeter.h"
#include "Components/ProgressBar.h"

void UShockMeter::NativeConstruct()
{
	ShockMeter->SetPercent(CurrentShock);
}

void UShockMeter::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	shockDecayTimer -= InDeltaTime;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Tick"));

	// reduce shock every second
	if (shockDecayTimer <= 0)
	{
		shockDecayTimer += 1;

		AddShock(-ShockDecayPerSecond);
	}
}

void UShockMeter::AddShock(float Value)
{
	CurrentShock += Value;

	UpdateProgressBar();
}

void UShockMeter::UpdateProgressBar()
{
	float NewPercentage = CalculatePercentage(CurrentShock, MinShock, MaxShock);

	ShockMeter->SetPercent(NewPercentage);
}

float UShockMeter::CalculatePercentage(float Value, float Min, float Max)
{
	float Percentage = Value / (Max - Min);

	return Percentage;
}
