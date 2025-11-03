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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	bool Detected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DetectedCooldown = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	bool SeeingPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Detection")
	float DetectionProgress = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float Distance = 0.f;

	UPROPERTY(EditAnywhere, Category = "Detection")
	TObjectPtr<UCurveFloat> GainCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float GainMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Detection")
	TObjectPtr<UCurveFloat> DecayCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DecayMultiplier = 1.f;

protected:

	float GetCurveValueAtX(TObjectPtr<UCurveFloat> curve, float x);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spook")
	float SpookDecayTime = 10;

	float SpookTimer = 0;

	float DetectedCooldownTimer;
};
