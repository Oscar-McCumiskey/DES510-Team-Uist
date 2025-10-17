// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/ShockMeter.h"
#include "Components/ProgressBar.h"

void UShockMeter::NativeConstruct()
{
	Super::NativeConstruct();

	ShockMeter->SetPercent(CurrentShock);
}

void UShockMeter::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	shockDecayTimer -= InDeltaTime;

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

	// Prevent shock dropping below minimum
	if (CurrentShock < MinShock)
	{
		CurrentShock = MinShock;
	}

	UpdateProgressBar();
	OnShockChanged(Value);

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
