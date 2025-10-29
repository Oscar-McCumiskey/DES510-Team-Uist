// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DES510_Team_UistPlayerController.generated.h"

class UInputMappingContext;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class ADES510_Team_UistPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddShock(float Value);

	UFUNCTION(BlueprintCallable)
	float CalculatePercentage(float Value, float Min, float Max);

	UFUNCTION(BlueprintImplementableEvent)
	void OnShockChanged(float ChangeAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Shock")
	float CurrentShock = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Shock")
	float MinShock = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Shock")
	float MaxShock = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shock")
	float ShockDecayPerSecond = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shock")
	float ShockUpdateFrequencyPerSecond = 1.f;

private:
	// ShockTimer
	float shockDecayTimer = 1;

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
};
