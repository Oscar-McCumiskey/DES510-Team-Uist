// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PossessableAppliance.generated.h"

UCLASS()
class DES510_TEAM_UIST_API APossessableAppliance : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APossessableAppliance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
