// Copyright Exile Planet. All Rights Reserved.

#include "Vehicle/ExileVehicle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Player/ExileCharacter.h"
#include "ExilePlanet.h"

AExileVehicle::AExileVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Visual & Collision Mesh
	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	RootComponent = VehicleMesh;
	VehicleMesh->SetSimulatePhysics(false);
	VehicleMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);

	// Driver Seat Position
	DriverSeatPoint = CreateDefaultSubobject<USceneComponent>(TEXT("DriverSeatPoint"));
	DriverSeatPoint->SetupAttachment(RootComponent);
	DriverSeatPoint->SetRelativeLocation(FVector(0.0f, -40.0f, 120.0f));

	// Exit Egress Position (outside the driver door)
	ExitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPoint"));
	ExitPoint->SetupAttachment(RootComponent);
	ExitPoint->SetRelativeLocation(FVector(0.0f, -180.0f, 0.0f));

	// Cabin First-Person Camera
	CabinCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CabinCamera"));
	CabinCamera->SetupAttachment(DriverSeatPoint);
	CabinCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	CabinCamera->bAutoActivate = false;

	// Third-Person Chase Camera Boom
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	ThirdPersonSpringArm->SetupAttachment(RootComponent);
	ThirdPersonSpringArm->TargetArmLength = 750.0f;
	ThirdPersonSpringArm->SocketOffset = FVector(0.0f, 0.0f, 150.0f);
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	ThirdPersonSpringArm->bDoCollisionTest = true;

	// Third-Person Follow Camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	ThirdPersonCamera->bAutoActivate = true;
}

void AExileVehicle::BeginPlay()
{
	Super::BeginPlay();
	SetCameraMode(CurrentCameraMode);
}

void AExileVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Driving controls bindings
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AExileVehicle::Throttle);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AExileVehicle::Steer);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	// Actions
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AExileVehicle::OnExitVehicle);
	PlayerInputComponent->BindAction(TEXT("ToggleCamera"), IE_Pressed, this, &AExileVehicle::ToggleCameraMode);
}

bool AExileVehicle::CanInteract_Implementation(AExileCharacter* InteractingCharacter) const
{
	return CurrentDriver == nullptr;
}

void AExileVehicle::Interact_Implementation(AExileCharacter* InteractingCharacter)
{
	if (InteractingCharacter && !CurrentDriver)
	{
		InteractingCharacter->EnterVehicle(this);
	}
}

FText AExileVehicle::GetInteractionPrompt_Implementation() const
{
	return NSLOCTEXT("Exile", "EnterTruckPrompt", "Press [E] to Enter Cargo Truck");
}

void AExileVehicle::OnEnterVehicle(AExileCharacter* InDriver, AController* InController)
{
	if (!InDriver)
	{
		return;
	}

	CurrentDriver = InDriver;

	AController* ControllerToPossess = InController ? InController : InDriver->GetController();
	if (ControllerToPossess)
	{
		ControllerToPossess->Possess(this);
	}

	SetCameraMode(CurrentCameraMode);
}

void AExileVehicle::OnExitVehicle()
{
	if (!CurrentDriver)
	{
		return;
	}

	AExileCharacter* DriverToExit = CurrentDriver;
	CurrentDriver = nullptr;

	// Preserve controller from this vehicle before UnPossess
	AController* SavedController = GetController();

	// Teleport driver to exit point
	const FVector ExitLocation = ExitPoint ? ExitPoint->GetComponentLocation() : (GetActorLocation() - GetActorRightVector() * 200.0f);
	DriverToExit->SetActorLocation(ExitLocation);

	if (SavedController)
	{
		SavedController->UnPossess();
		SavedController->Possess(DriverToExit);
	}

	DriverToExit->ExitVehicle();
}

void AExileVehicle::ToggleCameraMode()
{
	if (CurrentCameraMode == EExileVehicleCameraMode::ThirdPerson)
	{
		SetCameraMode(EExileVehicleCameraMode::CabinFirstPerson);
	}
	else
	{
		SetCameraMode(EExileVehicleCameraMode::ThirdPerson);
	}
}

void AExileVehicle::SetCameraMode(EExileVehicleCameraMode NewMode)
{
	CurrentCameraMode = NewMode;

	if (CurrentCameraMode == EExileVehicleCameraMode::CabinFirstPerson)
	{
		if (ThirdPersonCamera)
		{
			ThirdPersonCamera->Deactivate();
		}
		if (CabinCamera)
		{
			CabinCamera->Activate();
		}
	}
	else
	{
		if (CabinCamera)
		{
			CabinCamera->Deactivate();
		}
		if (ThirdPersonCamera)
		{
			ThirdPersonCamera->Activate();
		}
	}
}

void AExileVehicle::Throttle(float Value)
{
	CurrentThrottle = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AExileVehicle::Steer(float Value)
{
	CurrentSteering = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AExileVehicle::Handbrake(bool bBraking)
{
	bIsHandbraking = bBraking;
}
