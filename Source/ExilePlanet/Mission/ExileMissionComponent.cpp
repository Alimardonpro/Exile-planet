// Copyright Exile Planet. All Rights Reserved.

#include "Mission/ExileMissionComponent.h"

UExileMissionComponent::UExileMissionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UExileMission* UExileMissionComponent::AssignMission(TSubclassOf<UExileMission> MissionClass)
{
	if (!MissionClass)
	{
		return nullptr;
	}

	UExileMission* NewMission = NewObject<UExileMission>(this, MissionClass);
	if (NewMission)
	{
		ActiveMission = NewMission;
		ActiveMission->StartMission();
		OnMissionStarted.Broadcast(ActiveMission);
	}
	return ActiveMission;
}

void UExileMissionComponent::NotifyZoneReached(FName ZoneID)
{
	if (!ActiveMission || ActiveMission->Status != EExileMissionStatus::InProgress)
	{
		return;
	}

	for (const FExileMissionObjectiveData& Obj : ActiveMission->Objectives)
	{
		if (Obj.TargetZoneID == ZoneID && !Obj.bIsCompleted)
		{
			ActiveMission->CompleteObjective(Obj.ObjectiveID);
			break;
		}
	}

	if (ActiveMission->Status == EExileMissionStatus::Completed)
	{
		CompletedMissions.Add(ActiveMission);
		OnMissionCompleted.Broadcast(ActiveMission);
		ActiveMission = nullptr;
	}
}
