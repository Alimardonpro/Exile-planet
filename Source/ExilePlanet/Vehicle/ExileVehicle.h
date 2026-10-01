// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player/ExileInteractableInterface.h"
#include "ExileVehicle.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UStaticMeshComponent;
class AExileCharacter;

/** Truck classification in Sector 7 colony */
UENUM(BlueprintType)
enum class EExileTruckType : uint8
{
	LightUtility UMETA(DisplayName = "Light Utility Truck"),
	HeavyCargo UMETA(DisplayName = "Heavy Cargo Hauler"),
	ArmoredTransport UMETA(DisplayName = "Armored Transport"),
	MiningExcavator UMETA(DisplayName = "Mining Excavator")
};

/** Active camera perspective */
UENUM(BlueprintType)
enum class EExileVehicleCameraMode : uint8
{
	ThirdPerson UMETA(DisplayName = "Third Person Chase"),
	CabinFirstPerson UMETA(DisplayName = "Interior Cabin")
};

/** Modular structure for vehicle performance & visual upgrades */
USTRUCT(BlueprintType)
struct FExileVehicleUpgradeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	float EnginePowerMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	float SuspensionStiffness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	float ArmorPlating = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	float FuelTankCapacity = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	int32 CargoSlots = 4;
};

/**
 * Base class for all drivable vehicles and heavy trucks in Exile Planet.
 */
UCLASS()
class EXILEPLANET_API AExileVehicle : public APawn, public IExileInteractableInterface
{
	GENERATED_BODY()

public:
	AExileVehicle();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// --- IExileInteractableInterface implementation ---
	virtual bool CanInteract_Implementation(AExileCharacter* InteractingCharacter) const override;
	virtual void Interact_Implementation(AExileCharacter* InteractingCharacter) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	// --- Boarding / Egress ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	virtual void OnEnterVehicle(AExileCharacter* InDriver, AController* InController = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	virtual void OnExitVehicle();

	UFUNCTION(BlueprintPure, Category = "Exile|Vehicle")
	bool HasDriver() const { return CurrentDriver != nullptr; }

	UFUNCTION(BlueprintPure, Category = "Exile|Vehicle")
	AExileCharacter* GetDriver() const { return CurrentDriver; }

	// --- Camera System ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void ToggleCameraMode();

	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void SetCameraMode(EExileVehicleCameraMode NewMode);

	// --- Driving Controls ---
	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void Throttle(float Value);

	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void Steer(float Value);

	UFUNCTION(BlueprintCallable, Category = "Exile|Vehicle")
	void Handbrake(bool bBraking);

	// --- Cargo & Specs ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Vehicle|Config")
	EExileTruckType TruckType = EExileTruckType::HeavyCargo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Vehicle|Config")
	float CargoCapacityKg = 12000.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Vehicle|Cargo")
	float CurrentCargoWeightKg = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Vehicle|Config")
	FExileVehicleUpgradeData Upgrades;

protected:
	// Vehicle visual & collision root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> VehicleMesh;

	// Driver seat anchor location
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DriverSeatPoint;

	// Safe disembark location next to driver door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> ExitPoint;

	// Interior cabin camera for realistic simulator driving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CabinCamera;

	// Third person chase camera spring arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> ThirdPersonSpringArm;

	// Third person chase camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> ThirdPersonCamera;

	// Active camera perspective
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Vehicle|Camera")
	EExileVehicleCameraMode CurrentCameraMode = EExileVehicleCameraMode::ThirdPerson;

	// Current driver character
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Exile|Vehicle")
	TObjectPtr<AExileCharacter> CurrentDriver;

	// Cached steering & throttle inputs for movement integration
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Vehicle")
	float CurrentThrottle = 0.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Vehicle")
	float CurrentSteering = 0.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Vehicle")
	bool bIsHandbraking = false;
};
