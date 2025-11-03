// Copyright Epic Games, Inc. All Rights Reserved.


#include "DES510_Team_UistPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void ADES510_Team_UistPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	shockDecayTimer -= DeltaTime;

	// reduce shock every second
	if (shockDecayTimer <= 0)
	{
		float shockDecay = 0;
		if (ShockUpdateFrequencyPerSecond < DeltaTime)
		{
			shockDecayTimer += DeltaTime;
			shockDecay = ShockDecayPerSecond * DeltaTime;
		}
		else
		{
			shockDecayTimer += ShockUpdateFrequencyPerSecond;
			shockDecay = ShockDecayPerSecond * ShockUpdateFrequencyPerSecond;
		}

		AddShock(-shockDecay);
	}
}

void ADES510_Team_UistPlayerController::AddShock(float Value)
{
	CurrentShock += Value;

	// Prevent shock dropping below minimum
	if (CurrentShock < MinShock)
	{
		CurrentShock = MinShock;
	}

	OnShockChanged(Value);
}

float ADES510_Team_UistPlayerController::CalculatePercentage(float Value, float Min, float Max)
{
	float Percentage = Value / (Max - Min);

	return Percentage;
}

void ADES510_Team_UistPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
