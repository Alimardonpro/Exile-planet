// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExileObjective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompletedSignature, UExileObjective*, CompletedObjective);

/**
 * Trackable narrative or intro tutorial objective.
 */
UCLASS(BlueprintType, Blueprintable)
class EXILEPLANET_API UExileObjective : public UObject
{
	GENERATED_BODY()

public:
	UExileObjective();

	UFUNCTION(BlueprintCallable, Category = "Exile|Objective")
	void Complete();

	UFUNCTION(BlueprintPure, Category = "Exile|Objective")
	bool IsCompleted() const { return bIsCompleted; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Objective")
	FName ObjectiveID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Objective")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Exile|Objective")
	FText Description;

	UPROPERTY(BlueprintAssignable, Category = "Exile|Objective")
	FOnObjectiveCompletedSignature OnObjectiveCompleted;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Objective")
	bool bIsCompleted = false;
};
