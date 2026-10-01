// Copyright Exile Planet. All Rights Reserved.

#include "Core/ExileGameMode.h"
#include "Core/ExileGameState.h"
#include "Core/ExilePlayerController.h"
#include "Core/ExilePlayerState.h"
#include "Player/ExileCharacter.h"

AExileGameMode::AExileGameMode()
{
	// Set default gameplay class foundation
	DefaultPawnClass = AExileCharacter::StaticClass();
	PlayerControllerClass = AExilePlayerController::StaticClass();
	GameStateClass = AExileGameState::StaticClass();
	PlayerStateClass = AExilePlayerState::StaticClass();
}
