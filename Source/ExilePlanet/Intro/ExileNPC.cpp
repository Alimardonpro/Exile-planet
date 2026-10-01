// Copyright Exile Planet. All Rights Reserved.

#include "Intro/ExileNPC.h"
#include "Intro/ExileDialogue.h"

AExileNPC::AExileNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	NPCName = NSLOCTEXT("Exile", "SupervisorName", "Supervisor Vane");
}

bool AExileNPC::CanInteract_Implementation(AExileCharacter* InteractingCharacter) const
{
	return true;
}

void AExileNPC::Interact_Implementation(AExileCharacter* InteractingCharacter)
{
	OnNPCDialogueTriggered.Broadcast(this, AssignedDialogue);
}

FText AExileNPC::GetInteractionPrompt_Implementation() const
{
	return FText::Format(NSLOCTEXT("Exile", "TalkToNPCPrompt", "Press [E] to Speak with {0}"), NPCName);
}
