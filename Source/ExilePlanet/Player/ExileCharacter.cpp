// Copyright Exile Planet. All Rights Reserved.

#include "Player/ExileCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/ExileInteractionComponent.h"
#include "Vehicle/ExileVehicle.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ExilePlanet.h"

AExileCharacter::AExileCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set collision capsule size
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Character rotation follows movement, not camera rotation directly
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 550.0f;
	GetCharacterMovement()->AirControl = 0.25f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 40.0f, 60.0f); // slight over-the-shoulder view
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;

	// Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Modular Interaction Component
	InteractionComponent = CreateDefaultSubobject<UExileInteractionComponent>(TEXT("InteractionComponent"));
}

void AExileCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AExileCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 1. Enhanced Input bindings (if UEnhancedInputComponent is used)
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExileCharacter::EnhancedMove);
		}
		if (LookAction)
		{
			EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExileCharacter::EnhancedLook);
		}
		if (JumpAction)
		{
			EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		if (SprintAction)
		{
			EnhancedInputComp->BindAction(SprintAction, ETriggerEvent::Started, this, &AExileCharacter::EnhancedSprintStart);
			EnhancedInputComp->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExileCharacter::EnhancedSprintStop);
		}
		if (InteractAction)
		{
			EnhancedInputComp->BindAction(InteractAction, ETriggerEvent::Started, this, &AExileCharacter::EnhancedInteract);
		}
	}

	// 2. Direct Axis Mappings for immediate out-of-the-box WASD and Mouse control
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AExileCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AExileCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AExileCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AExileCharacter::LookUp);

	// Direct Action Mappings
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AExileCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AExileCharacter::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AExileCharacter::TriggerInteraction);
}

void AExileCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AExileCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AExileCharacter::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AExileCharacter::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AExileCharacter::EnhancedMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	MoveForward(MovementVector.Y);
	MoveRight(MovementVector.X);
}

void AExileCharacter::EnhancedLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	Turn(LookAxisVector.X);
	LookUp(LookAxisVector.Y);
}

void AExileCharacter::EnhancedSprintStart(const FInputActionValue& Value)
{
	StartSprint();
}

void AExileCharacter::EnhancedSprintStop(const FInputActionValue& Value)
{
	StopSprint();
}

void AExileCharacter::EnhancedInteract(const FInputActionValue& Value)
{
	TriggerInteraction();
}

void AExileCharacter::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AExileCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AExileCharacter::TriggerInteraction()
{
	if (InteractionComponent)
	{
		InteractionComponent->PerformInteract();
	}
}

void AExileCharacter::EnterVehicle(AExileVehicle* VehicleToEnter)
{
	if (!VehicleToEnter || CurrentVehicle)
	{
		return;
	}

	AController* SavedController = GetController();
	if (!SavedController)
	{
		return;
	}

	CurrentVehicle = VehicleToEnter;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	SavedController->UnPossess();
	VehicleToEnter->OnEnterVehicle(this, SavedController);
}

void AExileCharacter::ExitVehicle()
{
	if (!CurrentVehicle)
	{
		return;
	}

	AExileVehicle* VehicleRef = CurrentVehicle;
	CurrentVehicle = nullptr;

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	if (VehicleRef->GetDriver() == this)
	{
		VehicleRef->OnExitVehicle();
	}
}
