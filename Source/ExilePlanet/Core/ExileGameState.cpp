// Copyright Exile Planet. All Rights Reserved.

#include "Core/ExileGameState.h"

AExileGameState::AExileGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AExileGameState::SetCurrentGamePhase(EExileGamePhase NewPhase)
{
	if (CurrentPhase != NewPhase)
	{
		CurrentPhase = NewPhase;
		OnGamePhaseChanged.Broadcast(CurrentPhase);
	}
}

void AExileGameState::SetAlertLevel(EExileAlertLevel NewLevel)
{
	if (AlertLevel != NewLevel)
	{
		AlertLevel = NewLevel;
		OnAlertLevelChanged.Broadcast(AlertLevel);
	}
}
