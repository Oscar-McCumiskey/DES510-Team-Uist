// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/RobotButlerController.h"

// Sets default values
ARobotButlerController::ARobotButlerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpookTimer = SpookDecayTime;
}

// Called when the game starts or when spawned
void ARobotButlerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARobotButlerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spook
	if (SpookCount >= MaxSpookCount)
	{
		IsSpooked = true;
		SpookTimer = SpookDecayTime;
		SpookCount = 0;
	}

	if (!IsSpooked)
	{
		if (SpookCount > 0)
		{
			SpookTimer -= DeltaTime;
		}
		if (SpookTimer <= 0)
		{
			SpookCount -= 1;
			SpookTimer = SpookDecayTime;
		}
	}

	// Detection
	if (SeeingPlayer && !Detected)
	{
		if (GainCurve) DetectionProgress += (DeltaTime * GetCurveValueAtX(GainCurve, Distance) * GainMultiplier);
	}
	else
	{
		if (DetectionProgress < 0)
		{
			DetectionProgress = 0;
		}
		else
		{
			if (DecayCurve) DetectionProgress -= (DeltaTime * GetCurveValueAtX(DecayCurve, DetectionProgress) * DecayMultiplier);
		}
	}

	if (DetectionProgress > 100)
	{
		DetectionProgress = 100;
		DetectedCooldownTimer = DetectedCooldown;
		Detected = true;
	}

	if (Detected)
	{
		DetectedCooldownTimer -= DeltaTime;

		if (DetectedCooldownTimer <= 0)
		{
			DetectionProgress = 0;
			Detected = false;
		}
	}
}

float ARobotButlerController::GetCurveValueAtX(TObjectPtr<UCurveFloat> curve, float x)
{
	return curve->GetFloatValue(x);
}
