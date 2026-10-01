// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExileMission.generated.h"

UENUM(BlueprintType)
enum class EExileMissionStatus : uint8
{
	NotStarted UMETA(DisplayName = "Not Started"),
	InProgress UMETA(DisplayName = "In Progress"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed")
};

UENUM(BlueprintType)
enum class EExileMissionType : uint8
{
	CargoDelivery UMETA(DisplayName = "Cargo Delivery"),
	IndustrialTransport UMETA(DisplayName = "Industrial Transport"),
	InspectionPatrol UMETA(DisplayName = "Inspection Patrol"),
	HazardCleanUp UMETA(DisplayName = "Hazard Clean-Up")
};

USTRUCT(BlueprintType)
struct FExileMissionObjectiveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FName ObjectiveID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	FName TargetZoneID = NAME_None;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Objective")
	bool bIsCompleted = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionStatusChangedSignature, EExileMissionStatus, NewStatus);

/**
 * Base data and runtime tracking unit for narrative and industrial missions.
 */
UCLASS(BlueprintType, Blueprintable)
class EXILEPLANET_API UExileMission : public UObject
{
	GENERATED_BODY()

public:
	UExileMission();

	UFUNCTION(BlueprintCallable, Category = "Exile|Mission")
	void StartMission();

	UFUNCTION(BlueprintCallable, Category = "Exile|Mission")
	void CompleteObjective(FName InObjectiveID);

	UFUNCTION(BlueprintCallable, Category = "Exile|Mission")
	void CompleteMission();

	UFUNCTION(BlueprintCallable, Category = "Exile|Mission")
	void FailMission();

	UFUNCTION(BlueprintPure, Category = "Exile|Mission")
	bool AreAllObjectivesCompleted() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	FName MissionID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	EExileMissionType MissionType = EExileMissionType::CargoDelivery;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	int32 RewardCredits = 250;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	int32 RewardReputation = 15;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Mission")
	TArray<FExileMissionObjectiveData> Objectives;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Mission")
	EExileMissionStatus Status = EExileMissionStatus::NotStarted;

	UPROPERTY(BlueprintAssignable, Category = "Exile|Mission")
	FOnMissionStatusChangedSignature OnMissionStatusChanged;
};
