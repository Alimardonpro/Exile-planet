// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/ExileInteractableInterface.h"
#include "ExileNPC.generated.h"

class UExileDialogueData;

UENUM(BlueprintType)
enum class EExileNPCRole : uint8
{
	PrisonSupervisor UMETA(DisplayName = "Colony Prison Supervisor"),
	SecurityEnforcer UMETA(DisplayName = "Security Enforcer Guard"),
	TruckMechanic UMETA(DisplayName = "Logistics Truck Mechanic"),
	PenalLaborer UMETA(DisplayName = "Fellow Prisoner / Laborer")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNPCDialogueTriggeredSignature, AExileNPC*, InteractedNPC, UExileDialogueData*, Dialogue);

/**
 * Base class for interactive NPCs in Sector 7 and intro sequence.
 */
UCLASS()
class EXILEPLANET_API AExileNPC : public ACharacter, public IExileInteractableInterface
{
	GENERATED_BODY()

public:
	AExileNPC();

	// --- IExileInteractableInterface implementation ---
	virtual bool CanInteract_Implementation(AExileCharacter* InteractingCharacter) const override;
	virtual void Interact_Implementation(AExileCharacter* InteractingCharacter) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|NPC")
	FText NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|NPC")
	EExileNPCRole NPCRole = EExileNPCRole::PrisonSupervisor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|NPC")
	TObjectPtr<UExileDialogueData> AssignedDialogue;

	UPROPERTY(BlueprintAssignable, Category = "Exile|NPC")
	FOnNPCDialogueTriggeredSignature OnNPCDialogueTriggered;
};
