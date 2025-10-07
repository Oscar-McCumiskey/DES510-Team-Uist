// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/RoombaAppliance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ARoombaAppliance::ARoombaAppliance()
{
}

void ARoombaAppliance::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Abilities
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARoombaAppliance::Move);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Input Failed"));
	}
}

void ARoombaAppliance::Ability1(const FInputActionValue& Value)
{
	Super::Ability1(Value);

	DoAbility2();
}

void ARoombaAppliance::Ability2(const FInputActionValue& Value)
{
	Super::Ability2(Value);

	DoAbility2();
}

void ARoombaAppliance::Move(const FInputActionValue& Value)
{
	DoMove();
}

void ARoombaAppliance::DoAbility1()
{
}

void ARoombaAppliance::DoAbility2()
{
}

void ARoombaAppliance::DoMove()
{
}
