// Copyright Exile Planet. All Rights Reserved.

#include "Intro/ExileIntroSequence.h"

AExileIntroSequence::AExileIntroSequence()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AExileIntroSequence::SetIntroStep(EExileIntroSequenceStep NewStep)
{
	if (CurrentStep != NewStep)
	{
		CurrentStep = NewStep;
		OnIntroStepChanged.Broadcast(CurrentStep);
	}
}

void AExileIntroSequence::AdvanceStep()
{
	const uint8 NextIndex = static_cast<uint8>(CurrentStep) + 1;
	if (NextIndex <= static_cast<uint8>(EExileIntroSequenceStep::IntroCompleted))
	{
		SetIntroStep(static_cast<EExileIntroSequenceStep>(NextIndex));
	}
}
