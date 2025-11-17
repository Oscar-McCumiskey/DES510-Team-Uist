// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShockGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DES510_TEAM_UIST_API UShockGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSensitivity = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TutorialsActive = true;
};
