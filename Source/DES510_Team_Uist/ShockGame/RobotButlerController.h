// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RobotButlerController.generated.h"

/**
 * 
 */
UCLASS()
class DES510_TEAM_UIST_API ARobotButlerController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotButlerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spook")
	int SpookCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spook")
	int MaxSpookCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spook")
	bool IsSpooked = false;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spook")
	float SpookDecayTime = 10;

	float SpookTimer = 0;
};
