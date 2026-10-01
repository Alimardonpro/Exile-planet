// Copyright Exile Planet. All Rights Reserved.

#include "Core/ExilePlayerController.h"
#include "UI/ExileHUDWidget.h"
#include "Vehicle/ExileVehicle.h"
#include "Player/ExileCharacter.h"
#include "Blueprint/UserWidget.h"

AExilePlayerController::AExilePlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}

void AExilePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Default to Game-Only input
	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);

	// Create HUD widget if class is specified
	if (IsLocalController() && HUDWidgetClass)
	{
		ActiveHUDWidget = CreateWidget<UExileHUDWidget>(this, HUDWidgetClass);
		if (ActiveHUDWidget)
		{
			ActiveHUDWidget->AddToViewport();
		}
	}
}

void AExilePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ActiveHUDWidget)
	{
		const bool bIsVehicle = InPawn->IsA<AExileVehicle>();
		ActiveHUDWidget->SetVehicleHUDVisible(bIsVehicle);
	}
}

void AExilePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AExilePlayerController::SetUIMode(bool bEnableUI)
{
	bShowMouseCursor = bEnableUI;
	bEnableClickEvents = bEnableUI;
	bEnableMouseOverEvents = bEnableUI;

	if (bEnableUI)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}
