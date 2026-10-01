// Copyright Exile Planet. All Rights Reserved.

#include "Player/ExileInteractionComponent.h"
#include "Player/ExileCharacter.h"
#include "Player/ExileInteractableInterface.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

UExileInteractionComponent::UExileInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f; // Optimized: tick every 100ms instead of every frame
}

void UExileInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterOwner = Cast<AExileCharacter>(GetOwner());
}

void UExileInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ScanForInteractables();
}

void UExileInteractionComponent::ScanForInteractables()
{
	if (!CharacterOwner)
	{
		CharacterOwner = Cast<AExileCharacter>(GetOwner());
		if (!CharacterOwner)
		{
			return;
		}
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	CharacterOwner->GetActorEyesViewPoint(ViewLocation, ViewRotation);

	const FVector TraceEnd = ViewLocation + (ViewRotation.Vector() * InteractionDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CharacterOwner);

	FHitResult HitResult;
	const bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		ViewLocation,
		TraceEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(TraceRadius),
		QueryParams
	);

	AActor* HitActor = bHit ? HitResult.GetActor() : nullptr;
	AActor* NewTarget = nullptr;

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UExileInteractableInterface::StaticClass()))
	{
		if (IExileInteractableInterface::Execute_CanInteract(HitActor, CharacterOwner))
		{
			NewTarget = HitActor;
		}
	}

	if (NewTarget != CurrentFocusedActor)
	{
		CurrentFocusedActor = NewTarget;

		if (CurrentFocusedActor)
		{
			const FText Prompt = IExileInteractableInterface::Execute_GetInteractionPrompt(CurrentFocusedActor);
			OnInteractableFound.Broadcast(Prompt);
		}
		else
		{
			OnInteractableLost.Broadcast();
		}
	}
}

bool UExileInteractionComponent::PerformInteract()
{
	if (!CharacterOwner)
	{
		CharacterOwner = Cast<AExileCharacter>(GetOwner());
	}

	if (CurrentFocusedActor && CharacterOwner)
	{
		if (IExileInteractableInterface::Execute_CanInteract(CurrentFocusedActor, CharacterOwner))
		{
			IExileInteractableInterface::Execute_Interact(CurrentFocusedActor, CharacterOwner);
			return true;
		}
	}

	return false;
}
