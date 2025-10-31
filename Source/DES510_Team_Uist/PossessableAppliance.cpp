// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableAppliance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Components/CapsuleComponent.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DES510_Team_UistPlayerController.h"

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
	StaticMesh->bDisallowNanite = true;
	StaticMesh->SetCollisionProfileName(TEXT("Possessable"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->ProbeSize = 6.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AutoPossessAI = EAutoPossessAI::Disabled;

	EnableAbilityOne = true;
	EnableAbilityTwo = true;
}

// Called when the game starts or when spawned
void APossessableAppliance::BeginPlay()
{
	Super::BeginPlay();
	
	for (UActorComponent* Component : GetComponents())
	{
		if (Component->GetName() == TEXT("OutlineComponent"))
		{
			OutlineComponent = Component;
		}
	}
	
	if (Possessor)
	{
		IsPossessed = true;
	}
}

// Called every frame
void APossessableAppliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AbilityOneOnCooldown)
	{
		AbilityOneCooldownTimer -= DeltaTime;

		if (AbilityOneCooldownTimer <= 0)
		{
			AbilityOneOnCooldown = false;
			AbilityOneCooldownTimer = 0;
		}
	}

	if (AbilityTwoOnCooldown)
	{
		AbilityTwoCooldownTimer -= DeltaTime;

		if (AbilityTwoCooldownTimer <= 0)
		{
			AbilityTwoOnCooldown = false;
			AbilityTwoCooldownTimer = 0;
		}
	}

	if (PossessingPlayerController)
	{
		if (PossessingPlayerController->CurrentShock >= AbilityOneUnlockThreshold)
		{
			EnableAbilityOne = true;
		}
		else
		{
			EnableAbilityOne = false;
		}

		if (PossessingPlayerController->CurrentShock >= AbilityTwoUnlockThreshold)
		{
			EnableAbilityTwo = true;
		}
		else
		{
			EnableAbilityTwo = false;
		}
	}
}

void APossessableAppliance::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	IsPossessed = true;

	PossessingPlayerController = Cast<ADES510_Team_UistPlayerController>(NewController);

	CallEventByName(TEXT("PossessedOutline"));
}

void APossessableAppliance::UnPossessed()
{
	Super::UnPossessed();

	IsPossessed = false;

	PossessingPlayerController = nullptr;

	CallEventByName(TEXT("NeutralOutline"));
}

void APossessableAppliance::Interacted_Implementation()
{
	CallEventByName(TEXT("SelectedOutline"));
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
		EnhancedInputComponent->BindAction(AbilityOneAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Ability1);
		EnhancedInputComponent->BindAction(AbilityTwoAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Ability2);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Interact);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Look);

		// Zooming
		EnhancedInputComponent->BindAction(MouseZoomAction, ETriggerEvent::Triggered, this, &APossessableAppliance::Zoom);
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

void APossessableAppliance::Ability1(const FInputActionValue& Value)
{
	// Use Ability One
	if (!AbilityOneOnCooldown && EnableAbilityOne)
	{
		AbilityOneCooldownTimer = AbilityOneCooldownTime;
		AbilityOneOnCooldown = true;
		DoAbility1();
		DoAbilityOneBlueprint();
	}
}

void APossessableAppliance::Ability2(const FInputActionValue& Value)
{
	// Use Ability Two
	if (!AbilityTwoOnCooldown && EnableAbilityTwo)
	{
		AbilityTwoCooldownTimer = AbilityTwoCooldownTime;
		AbilityTwoOnCooldown = true;
		DoAbility2();
		DoAbilityTwoBlueprint();
	}
}

void APossessableAppliance::Interact(const FInputActionValue& Value)
{
	DoInteract();
}

void APossessableAppliance::Zoom(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>();
	ZoomValue *= ZoomSpeed;
	DoZoom(ZoomValue);
}

void APossessableAppliance::CallEventByName(FName Name)
{
	if (OutlineComponent)
	{
		UFunction* Function = OutlineComponent->FindFunction(Name);
		if (Function)
		{
			OutlineComponent->ProcessEvent(Function, nullptr);
		}
	}
}

void APossessableAppliance::GetCooldownTimes(float& AbilityOneTimeRemainingOut, float& AbilityOneCooldownTimeOut, float& AbilityTwoTimeRemainingOut, float& AbilityTwoCooldownTimeOut) const
{
	AbilityOneCooldownTimeOut = AbilityOneCooldownTime;
	AbilityOneTimeRemainingOut = AbilityOneCooldownTimer;

	AbilityTwoCooldownTimeOut = AbilityTwoCooldownTime;
	AbilityTwoTimeRemainingOut = AbilityTwoCooldownTimer;
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

void APossessableAppliance::DoAbility1()
{
	// Ability One Logic
}

void APossessableAppliance::DoAbility2()
{
	// Ability Two Logic
}

void APossessableAppliance::DoInteract()
{
	// Interact Logic
	Controller->Possess(Possessor);
}

void APossessableAppliance::DoZoom(float ArmLengthChange)
{
	float newArmLength = ArmLengthChange + CameraBoom->TargetArmLength;
	CameraBoom->TargetArmLength = FMath::Clamp(newArmLength, MinCameraDistance, MaxCameraDistance);
}

