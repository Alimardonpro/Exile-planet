// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExileMissionZone.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMissionZoneTriggeredSignature, FName, ZoneID, AActor*, TriggeringActor);

/**
 * World zone volume identifying mission dropoffs, loading docks, and checkpoints.
 */
UCLASS()
class EXILEPLANET_API AExileMissionZone : public AActor
{
	GENERATED_BODY()

public:
	AExileMissionZone();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|MissionZone")
	FName ZoneID = TEXT("Zone_Sector7_Default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|MissionZone")
	FText ZoneDisplayName;

	UPROPERTY(BlueprintAssignable, Category = "Exile|MissionZone")
	FOnMissionZoneTriggeredSignature OnZoneTriggered;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox;
};
