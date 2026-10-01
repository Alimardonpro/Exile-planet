// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ExilePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChangedSignature, int32, NewCredits);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReputationChangedSignature, int32, NewReputation);

/**
 * Stores player progression, criminal convict ID, credits, reputation, and vehicle assignment.
 */
UCLASS()
class EXILEPLANET_API AExilePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AExilePlayerState();

	// --- Prisoner Identity ---
	UFUNCTION(BlueprintPure, Category = "Exile|PlayerState")
	FString GetPrisonerID() const { return PrisonerID; }

	UFUNCTION(BlueprintCallable, Category = "Exile|PlayerState")
	void SetPrisonerID(const FString& InID) { PrisonerID = InID; }

	// --- Financial & Colony Progression ---
	UFUNCTION(BlueprintPure, Category = "Exile|PlayerState")
	int32 GetCredits() const { return Credits; }

	UFUNCTION(BlueprintCallable, Category = "Exile|PlayerState")
	void AddCredits(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Exile|PlayerState")
	bool DeductCredits(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Exile|PlayerState")
	int32 GetColonyReputation() const { return ColonyReputation; }

	UFUNCTION(BlueprintCallable, Category = "Exile|PlayerState")
	void AdjustReputation(int32 Delta);

	// --- Assigned Vehicle ---
	UFUNCTION(BlueprintPure, Category = "Exile|PlayerState")
	FName GetAssignedTruckID() const { return AssignedTruckID; }

	UFUNCTION(BlueprintCallable, Category = "Exile|PlayerState")
	void SetAssignedTruckID(FName NewTruckID) { AssignedTruckID = NewTruckID; }

	UPROPERTY(BlueprintAssignable, Category = "Exile|PlayerState")
	FOnCreditsChangedSignature OnCreditsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Exile|PlayerState")
	FOnReputationChangedSignature OnReputationChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Prisoner")
	FString PrisonerID = TEXT("PRISONER #7041");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Prisoner")
	int32 Credits = 150;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Prisoner")
	int32 ColonyReputation = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Prisoner")
	FName AssignedTruckID = NAME_None;
};
