// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mission/ExileMission.h"
#include "ExileMissionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionStartedSignature, UExileMission*, Mission);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionCompletedSignature, UExileMission*, Mission);

/**
 * Reusable mission manager component. Can be attached to PlayerController, PlayerState, or GameState.
 */
UCLASS(ClassGroup=(Exile), meta=(BlueprintSpawnableComponent))
class EXILEPLANET_API UExileMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UExileMissionComponent();

	UFUNCTION(BlueprintCallable, Category = "Exile|Missions")
	UExileMission* AssignMission(TSubclassOf<UExileMission> MissionClass);

	UFUNCTION(BlueprintCallable, Category = "Exile|Missions")
	void NotifyZoneReached(FName ZoneID);

	UFUNCTION(BlueprintPure, Category = "Exile|Missions")
	UExileMission* GetActiveMission() const { return ActiveMission; }

	UFUNCTION(BlueprintPure, Category = "Exile|Missions")
	const TArray<UExileMission*>& GetCompletedMissions() const { return CompletedMissions; }

	UPROPERTY(BlueprintAssignable, Category = "Exile|Missions")
	FOnMissionStartedSignature OnMissionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Exile|Missions")
	FOnMissionCompletedSignature OnMissionCompleted;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Missions")
	TObjectPtr<UExileMission> ActiveMission;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Missions")
	TArray<TObjectPtr<UExileMission>> CompletedMissions;
};
