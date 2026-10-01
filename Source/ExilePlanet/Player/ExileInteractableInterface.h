// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExileInteractableInterface.generated.h"

class AExileCharacter;

UINTERFACE(MinimalAPI, Blueprintable)
class UExileInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Reusable interactable interface implemented by vehicles, NPCs, mission terminals, and world props.
 */
class EXILEPLANET_API IExileInteractableInterface
{
	GENERATED_BODY()

public:
	/** Checks if interaction is currently available for this character */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exile|Interaction")
	bool CanInteract(AExileCharacter* InteractingCharacter) const;

	/** Executes the interaction */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exile|Interaction")
	void Interact(AExileCharacter* InteractingCharacter);

	/** Returns user-facing prompt text (e.g. "Enter Truck", "Talk to Supervisor") */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exile|Interaction")
	FText GetInteractionPrompt() const;
};
