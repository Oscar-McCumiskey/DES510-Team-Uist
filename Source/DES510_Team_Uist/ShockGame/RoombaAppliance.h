// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PossessableAppliance.h"
#include "RoombaAppliance.generated.h"

/**
 * 
 */
UCLASS()
class DES510_TEAM_UIST_API ARoombaAppliance : public APossessableAppliance
{
	GENERATED_BODY()
	
public:
	ARoombaAppliance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Ability1(const FInputActionValue& Value) override;

	virtual void Ability2(const FInputActionValue& Value) override;

	void Move(const FInputActionValue& Value);

public:
	// Execute Abilities
	virtual void DoAbility1() override;

	virtual void DoAbility2() override;

	void DoMove();
};
