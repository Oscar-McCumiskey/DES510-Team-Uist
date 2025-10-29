// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShockMeter.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS()
class DES510_TEAM_UIST_API UShockMeter : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void UpdateProgressBar(float Shock);

	// Bind Widget to C++
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ShockMeter;
};
