// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PossessableAppliance.h"
#include "LightAppliance.generated.h"

/**
 * 
 */
class UPointLightComponent;

UCLASS()
class DES510_TEAM_UIST_API ALightAppliance : public APossessableAppliance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* LightComponent;

public:
	ALightAppliance();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Light")
	virtual void SetIntensity(float Intensity);

	virtual void DoAbility1() override;

	virtual void DoAbility2() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float LightOffTime = 1.f;

	float lightoffTimer = 0.f;

	float initialIntensity;
};
