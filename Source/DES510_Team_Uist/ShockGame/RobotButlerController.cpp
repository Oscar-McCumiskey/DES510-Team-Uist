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
}
