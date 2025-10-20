// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockGame/AICharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpookTimer = SpookDecayTime;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

