// Copyright Exile Planet. All Rights Reserved.

#include "Mission/ExileMissionZone.h"
#include "Components/BoxComponent.h"
#include "Mission/ExileMissionComponent.h"

AExileMissionZone::AExileMissionZone()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(300.0f, 300.0f, 200.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void AExileMissionZone::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AExileMissionZone::OnOverlapBegin);
}

void AExileMissionZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		OnZoneTriggered.Broadcast(ZoneID, OtherActor);

		// If triggering actor has a mission component, notify directly
		if (UExileMissionComponent* MissionComp = OtherActor->FindComponentByClass<UExileMissionComponent>())
		{
			MissionComp->NotifyZoneReached(ZoneID);
		}
	}
}
