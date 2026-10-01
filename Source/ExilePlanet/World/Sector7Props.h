// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/ExileInteractableInterface.h"
#include "Sector7Props.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class ESector7PropCategory : uint8
{
	CargoContainer UMETA(DisplayName = "Cargo Container"),
	IndustrialMachinery UMETA(DisplayName = "Industrial Machinery"),
	SecurityBarrier UMETA(DisplayName = "Security Barrier"),
	FloodlightTower UMETA(DisplayName = "Floodlight Tower"),
	ColonyTerminal UMETA(DisplayName = "Interactive Colony Terminal")
};

/**
 * Base actor for industrial Sector 7 props, cargo containers, and machinery.
 */
UCLASS()
class EXILEPLANET_API ASector7Prop : public AActor, public IExileInteractableInterface
{
	GENERATED_BODY()

public:
	ASector7Prop();

	// --- IExileInteractableInterface implementation ---
	virtual bool CanInteract_Implementation(AExileCharacter* InteractingCharacter) const override;
	virtual void Interact_Implementation(AExileCharacter* InteractingCharacter) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Props")
	ESector7PropCategory Category = ESector7PropCategory::CargoContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Props")
	bool bIsInteractable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Props", meta = (EditCondition = "bIsInteractable"))
	FText InteractionPromptText;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PropMesh;
};
