// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExileHUDWidget.generated.h"

/**
 * Base user widget for player HUD, interaction reticle, mission tracker, and vehicle instrumentation.
 */
UCLASS()
class EXILEPLANET_API UExileHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// --- Prompt HUD ---
	UFUNCTION(BlueprintImplementableEvent, Category = "Exile|HUD")
	void ShowInteractionPrompt(const FText& PromptText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Exile|HUD")
	void HideInteractionPrompt();

	// --- Objective HUD ---
	UFUNCTION(BlueprintImplementableEvent, Category = "Exile|HUD")
	void UpdateObjectiveText(const FText& ObjectiveTitle, const FText& ObjectiveDesc);

	// --- Vehicle HUD ---
	UFUNCTION(BlueprintImplementableEvent, Category = "Exile|HUD")
	void SetVehicleHUDVisible(bool bVisible);

	UFUNCTION(BlueprintImplementableEvent, Category = "Exile|HUD")
	void UpdateVehicleStats(float SpeedKph, float ThrottlePercent, float CargoWeightKg);
};
