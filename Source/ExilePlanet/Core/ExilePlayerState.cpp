// Copyright Exile Planet. All Rights Reserved.

#include "Core/ExilePlayerState.h"

AExilePlayerState::AExilePlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AExilePlayerState::AddCredits(int32 Amount)
{
	if (Amount > 0)
	{
		Credits += Amount;
		OnCreditsChanged.Broadcast(Credits);
	}
}

bool AExilePlayerState::DeductCredits(int32 Amount)
{
	if (Amount > 0 && Credits >= Amount)
	{
		Credits -= Amount;
		OnCreditsChanged.Broadcast(Credits);
		return true;
	}
	return false;
}

void AExilePlayerState::AdjustReputation(int32 Delta)
{
	ColonyReputation += Delta;
	OnReputationChanged.Broadcast(ColonyReputation);
}
