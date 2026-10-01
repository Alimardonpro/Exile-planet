// Copyright Exile Planet. All Rights Reserved.

#include "Intro/ExileObjective.h"

UExileObjective::UExileObjective()
{
}

void UExileObjective::Complete()
{
	if (!bIsCompleted)
	{
		bIsCompleted = true;
		OnObjectiveCompleted.Broadcast(this);
	}
}
