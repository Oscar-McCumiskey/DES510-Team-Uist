// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/LightAppliance.h"
#include "Components/PointLightComponent.h"

ALightAppliance::ALightAppliance()
{
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	
	LightComponent->SetupAttachment(RootComponent);
	LightComponent->SetLightColor(FColor::White);
	LightComponent->SetIntensityUnits(ELightUnits::Candelas);
	LightComponent->SetIntensity(8.f);
	LightComponent->SetAttenuationRadius(1000.f);
	LightComponent->SetSourceRadius(0.f);
	LightComponent->SetUseTemperature(true);
	LightComponent->SetTemperature(5000.f);

	initialIntensity = LightComponent->Intensity;
}

void ALightAppliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (lightoffTimer > 0)
	{
		lightoffTimer -= DeltaTime;
	}
	else
	{
		LightComponent->SetIntensity(initialIntensity);
		SetLightMaterialIntensity(1.f);
	}*/
}

void ALightAppliance::SetIntensity(float Intensity)
{
	LightComponent->SetIntensity(Intensity);
	initialIntensity = Intensity;
}

void ALightAppliance::DoAbility1()
{
	/*LightComponent->SetIntensity(0.f);
	lightoffTimer = LightOffTime;
	SetLightMaterialIntensity(0.f);*/
}

void ALightAppliance::DoAbility2()
{

}
