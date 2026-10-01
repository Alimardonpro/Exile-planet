// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ExileCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UExileInteractionComponent;
class AExileVehicle;
class UInputAction;

UCLASS()
class EXILEPLANET_API AExileCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AExileCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// --- Movement & Sprint ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Movement")
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category = "Exile|Movement")
	void StopSprint();

	UFUNCTION(BlueprintPure, Category = "Exile|Movement")
	bool IsSprinting() const { return bIsSprinting; }

	// --- Vehicle System Hooks ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void EnterVehicle(AExileVehicle* VehicleToEnter);

	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void ExitVehicle();

	UFUNCTION(BlueprintPure, Category = "Exile|Vehicle")
	bool IsInVehicle() const { return CurrentVehicle != nullptr; }

	UFUNCTION(BlueprintPure, Category = "Exile|Vehicle")
	AExileVehicle* GetCurrentVehicle() const { return CurrentVehicle; }

	// --- Interaction ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Interaction")
	void TriggerInteraction();

	// --- Components ---
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UExileInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

protected:
	// Legacy / Direct Axis Input Handlers
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// Enhanced Input Handlers
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);
	void EnhancedInteract(const FInputActionValue& Value);
	void EnhancedSprintStart(const FInputActionValue& Value);
	void EnhancedSprintStop(const FInputActionValue& Value);

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Modular interaction component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UExileInteractionComponent> InteractionComponent;

	// Movement settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Movement")
	float WalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Movement")
	float SprintSpeed = 850.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Movement")
	bool bIsSprinting = false;

	// Vehicle reference
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Exile|Vehicle")
	TObjectPtr<AExileVehicle> CurrentVehicle;

	// Enhanced Input Actions (optional, configured via BP or defaults)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Input")
	TObjectPtr<UInputAction> InteractAction;
};
