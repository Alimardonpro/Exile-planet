// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExileIntroSequence.generated.h"

class AExileNPC;
class AExileVehicle;
class AExileMissionZone;

/**
 * Stages of the first narrative playable sequence in Exile Planet.
 */
UENUM(BlueprintType)
enum class EExileIntroSequenceStep : uint8
{
	PrisonTransportShip UMETA(DisplayName = "1. Prison Transport Ship In Orbit"),
	LandingOnAlienPlanet UMETA(DisplayName = "2. Landing On Alien Planet"),
	PrisonerExitsShip UMETA(DisplayName = "3. Prisoner Exits Ship"),
	MeetsSupervisor UMETA(DisplayName = "4. Meets Supervisor"),
	ReceivesFirstObjective UMETA(DisplayName = "5. Receives First Objective"),
	WalksToAssignedTruck UMETA(DisplayName = "6. Walks to Assigned Truck"),
	EntersTruck UMETA(DisplayName = "7. Enters Truck"),
	FirstCargoDelivery UMETA(DisplayName = "8. First Cargo Delivery"),
	IntroCompleted UMETA(DisplayName = "9. Intro Sequence Completed")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntroStepChangedSignature, EExileIntroSequenceStep, CurrentStep);

/**
 * Manages the chronological introductory sequence from prison transport arrival to first cargo run.
 */
UCLASS()
class EXILEPLANET_API AExileIntroSequence : public AActor
{
	GENERATED_BODY()

public:
	AExileIntroSequence();

	UFUNCTION(BlueprintCallable, Category = "Exile|Intro")
	void SetIntroStep(EExileIntroSequenceStep NewStep);

	UFUNCTION(BlueprintCallable, Category = "Exile|Intro")
	void AdvanceStep();

	UFUNCTION(BlueprintPure, Category = "Exile|Intro")
	EExileIntroSequenceStep GetCurrentStep() const { return CurrentStep; }

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Intro")
	EExileIntroSequenceStep CurrentStep = EExileIntroSequenceStep::PrisonTransportShip;

	UPROPERTY(BlueprintAssignable, Category = "Exile|Intro")
	FOnIntroStepChangedSignature OnIntroStepChanged;

	// Key sequence references
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Exile|Intro|Actors")
	TObjectPtr<AExileNPC> SupervisorNPC;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Exile|Intro|Actors")
	TObjectPtr<AExileVehicle> AssignedTruck;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Exile|Intro|Actors")
	TObjectPtr<AExileMissionZone> FirstDeliveryZone;
};
