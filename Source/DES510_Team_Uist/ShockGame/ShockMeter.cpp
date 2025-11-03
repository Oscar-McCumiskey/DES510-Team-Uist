// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/ShockMeter.h"
#include "Components/ProgressBar.h"

void UShockMeter::UpdateProgressBar(float Shock)
{
	ShockMeter->SetPercent(Shock);
}
