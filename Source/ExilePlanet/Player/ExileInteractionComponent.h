// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExileInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFoundSignature, const FText&, PromptText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLostSignature);

class AExileCharacter;

UCLASS(ClassGroup=(Exile), meta=(BlueprintSpawnableComponent))
class EXILEPLANET_API UExileInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UExileInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Trigger interaction with currently focused interactable */
	UFUNCTION(BlueprintCallable, Category = "Exile|Interaction")
	bool PerformInteract();

	/** Gets currently focused interactable actor */
	UFUNCTION(BlueprintCallable, Category = "Exile|Interaction")
	AActor* GetFocusedActor() const { return CurrentFocusedActor; }

	/** Max distance for interaction trace (in cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Interaction")
	float InteractionDistance = 350.0f;

	/** Radius of trace sphere */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Interaction")
	float TraceRadius = 40.0f;

	/** Broadcast when an interactable is detected in range */
	UPROPERTY(BlueprintAssignable, Category = "Exile|Interaction")
	FOnInteractableFoundSignature OnInteractableFound;

	/** Broadcast when interactable is no longer in range */
	UPROPERTY(BlueprintAssignable, Category = "Exile|Interaction")
	FOnInteractableLostSignature OnInteractableLost;

protected:
	void ScanForInteractables();

	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentFocusedActor;

	UPROPERTY(Transient)
	TObjectPtr<AExileCharacter> CharacterOwner;
};
