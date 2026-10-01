// Copyright Exile Planet. All Rights Reserved.

#include "Mission/ExileMission.h"

UExileMission::UExileMission()
{
}

void UExileMission::StartMission()
{
	if (Status == EExileMissionStatus::NotStarted)
	{
		Status = EExileMissionStatus::InProgress;
		OnMissionStatusChanged.Broadcast(Status);
	}
}

void UExileMission::CompleteObjective(FName InObjectiveID)
{
	if (Status != EExileMissionStatus::InProgress)
	{
		return;
	}

	for (FExileMissionObjectiveData& Obj : Objectives)
	{
		if (Obj.ObjectiveID == InObjectiveID && !Obj.bIsCompleted)
		{
			Obj.bIsCompleted = true;
			break;
		}
	}

	if (AreAllObjectivesCompleted())
	{
		CompleteMission();
	}
}

void UExileMission::CompleteMission()
{
	Status = EExileMissionStatus::Completed;
	OnMissionStatusChanged.Broadcast(Status);
}

void UExileMission::FailMission()
{
	Status = EExileMissionStatus::Failed;
	OnMissionStatusChanged.Broadcast(Status);
}

bool UExileMission::AreAllObjectivesCompleted() const
{
	if (Objectives.Num() == 0)
	{
		return true;
	}

	for (const FExileMissionObjectiveData& Obj : Objectives)
	{
		if (!Obj.bIsCompleted)
		{
			return false;
		}
	}

	return true;
}
