// Copyright Exile Planet. All Rights Reserved.

#include "World/Sector7Props.h"
#include "Components/StaticMeshComponent.h"

ASector7Prop::ASector7Prop()
{
	PrimaryActorTick.bCanEverTick = false;

	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropMesh"));
	RootComponent = PropMesh;
	PropMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	InteractionPromptText = NSLOCTEXT("Exile", "DefaultPropPrompt", "Press [E] to Inspect Terminal");
}

bool ASector7Prop::CanInteract_Implementation(AExileCharacter* InteractingCharacter) const
{
	return bIsInteractable;
}

void ASector7Prop::Interact_Implementation(AExileCharacter* InteractingCharacter)
{
	// Base implementation can be extended in Blueprint or specialized subclasses
}

FText ASector7Prop::GetInteractionPrompt_Implementation() const
{
	return InteractionPromptText;
}
