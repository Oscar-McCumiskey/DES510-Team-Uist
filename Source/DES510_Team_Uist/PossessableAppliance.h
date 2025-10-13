// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PossessableAppliance.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class DES510_TEAM_UIST_API APossessableAppliance : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	APossessableAppliance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Appliance Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MouseLookAction;

	/** Mouse Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MouseZoomAction;

	/** Ability Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	APawn* Possessor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	bool OnCooldown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	float CooldownTime = 0.f;

	float CooldownTimer = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float MinCameraDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float MaxCameraDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomSpeed = 20.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Look(const FInputActionValue& Value);

	void Ability1(const FInputActionValue& Value);

	void Ability2(const FInputActionValue& Value);

	virtual void Interact(const FInputActionValue& Value);

	virtual void Zoom(const FInputActionValue& Value);

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	// Execute Abilities
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAbility1();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void DoAbility1Blueprint();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAbility2();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void DoAbility2Blueprint();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoInteract();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoZoom(float ArmLengthChange);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
