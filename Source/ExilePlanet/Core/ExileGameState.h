// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExileGameState.generated.h"

/** Broad gameplay narrative phase */
UENUM(BlueprintType)
enum class EExileGamePhase : uint8
{
	PrisonerTransportShip UMETA(DisplayName = "Prisoner Transport Ship"),
	Sector7Arrival UMETA(DisplayName = "Sector 7 Arrival"),
	WorkAssignment UMETA(DisplayName = "Work Assignment"),
	OpenWorldExploration UMETA(DisplayName = "Open World Exploration"),
	ColonyLockdown UMETA(DisplayName = "Colony Lockdown")
};

/** Colony security alert status */
UENUM(BlueprintType)
enum class EExileAlertLevel : uint8
{
	CodeGreen UMETA(DisplayName = "Standard Industrial Operations"),
	CodeYellow UMETA(DisplayName = "Elevated Hazard / Inspection"),
	CodeOrange UMETA(DisplayName = "Quarantine Breach"),
	CodeRed UMETA(DisplayName = "Sector Lockdown")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseChangedSignature, EExileGamePhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlertLevelChangedSignature, EExileAlertLevel, NewAlertLevel);

/**
 * Game state managing shared planetary colony conditions and narrative progression.
 */
UCLASS()
class EXILEPLANET_API AExileGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AExileGameState();

	UFUNCTION(BlueprintPure, Category = "Exile|GameState")
	EExileGamePhase GetCurrentGamePhase() const { return CurrentPhase; }

	UFUNCTION(BlueprintCallable, Category = "Exile|GameState")
	void SetCurrentGamePhase(EExileGamePhase NewPhase);

	UFUNCTION(BlueprintPure, Category = "Exile|GameState")
	EExileAlertLevel GetAlertLevel() const { return AlertLevel; }

	UFUNCTION(BlueprintCallable, Category = "Exile|GameState")
	void SetAlertLevel(EExileAlertLevel NewLevel);

	UPROPERTY(BlueprintAssignable, Category = "Exile|GameState")
	FOnGamePhaseChangedSignature OnGamePhaseChanged;

	UPROPERTY(BlueprintAssignable, Category = "Exile|GameState")
	FOnAlertLevelChangedSignature OnAlertLevelChanged;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|GameState")
	EExileGamePhase CurrentPhase = EExileGamePhase::Sector7Arrival;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|GameState")
	EExileAlertLevel AlertLevel = EExileAlertLevel::CodeGreen;
};
