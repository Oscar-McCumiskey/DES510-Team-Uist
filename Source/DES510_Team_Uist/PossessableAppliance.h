// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShockGame/Possessable.h"
#include "PossessableAppliance.generated.h"

class ADES510_Team_UistPlayerController;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class DES510_TEAM_UIST_API APossessableAppliance : public APawn, public IPossessable
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
	UInputAction* AbilityOneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* AbilityTwoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

protected:

	ADES510_Team_UistPlayerController* PossessingPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	APawn* Possessor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appliance")
	bool IsPossessed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	bool AbilityOneOnCooldown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	bool AbilityTwoOnCooldown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	float AbilityOneCooldownTime = 0.f;

	float AbilityOneCooldownTimer = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	float AbilityTwoCooldownTime = 0.f;

	float AbilityTwoCooldownTimer = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	float AbilityOneUnlockThreshold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	bool EnableAbilityOne = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	float AbilityTwoUnlockThreshold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appliance")
	bool EnableAbilityTwo = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float MinCameraDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float MaxCameraDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomSpeed = 20.f;

protected:

	UActorComponent* OutlineComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	virtual void Interacted_Implementation() override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Look(const FInputActionValue& Value);

	void Ability1(const FInputActionValue& Value);

	void Ability2(const FInputActionValue& Value);

	virtual void Interact(const FInputActionValue& Value);

	virtual void Zoom(const FInputActionValue& Value);

private:

	void CallEventByName(FName Name);

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void GetCooldownTimes(float& AbilityOneTimeRemainingOut, float& AbilityOneCooldownTimeOut, float& AbilityTwoTimeRemainingOut, float& AbilityTwoCooldownTimeOut) const;

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	// Execute Abilities
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAbility1();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void DoAbilityOneBlueprint();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAbility2();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void DoAbilityTwoBlueprint();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoInteract();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoZoom(float ArmLengthChange);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
