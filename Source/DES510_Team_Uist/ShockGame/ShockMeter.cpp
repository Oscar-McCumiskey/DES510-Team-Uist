// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/ShockMeter.h"
#include "Components/ProgressBar.h"

void UShockMeter::AddShock(float Value)
{
}

float UShockMeter::CalculatePercentage(float Value, float Min, float Max)
{
	return Value / (Max - Min);
}
