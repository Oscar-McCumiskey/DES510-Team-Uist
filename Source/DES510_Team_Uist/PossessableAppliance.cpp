// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableAppliance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Components/CapsuleComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
APossessableAppliance::APossessableAppliance()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character rotation only changes in Yaw, to prevent the capsule from changing orientation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Create capsule component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(96.0f, 96.0f);
	CapsuleComponent->SetMobility(EComponentMobility::Static);
	CapsuleComponent->SetEnableGravity(false);

	// Create static mesh
	StaticMesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Appliance Model"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetMobility(EComponentMobility::Static);
	StaticMesh->SetEnableGravity(false);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APossessableAppliance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APossessableAppliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APossessableAppliance::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Abilities
		EnhancedInputComponent->BindAction(AbilityOneAction, ETriggerEvent::Triggered, this, &APossessableAppliance::AbilityOne);
		EnhancedInputComponent->BindAction(AbilityTwoAction, ETriggerEvent::Triggered, this, &APossessableAppliance::AbilityTwo);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Interact);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Look);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Input Failed"));
	}
}

void APossessableAppliance::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APossessableAppliance::AbilityOne(const FInputActionValue& Value)
{
	// Use Ability One
	DoAbilityOne();
}

void APossessableAppliance::AbilityTwo(const FInputActionValue& Value)
{
	// Use Ability Two
	DoAbilityTwo();
}

void APossessableAppliance::Interact(const FInputActionValue& Value)
{
	DoInteract();
}

void APossessableAppliance::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APossessableAppliance::DoAbilityOne()
{
	// Ability One Logic
}

void APossessableAppliance::DoAbilityTwo()
{
	// Ability Two Logic
}

void APossessableAppliance::DoInteract()
{
	// Interact Logic
	Controller->Possess(Possessor);
}

