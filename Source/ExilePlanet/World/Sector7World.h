// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector7World.generated.h"

class ASector7District;
class ASector7Environment;

/**
 * World master manager for the Sector 7 penal colony.
 */
UCLASS()
class EXILEPLANET_API ASector7World : public AActor
{
	GENERATED_BODY()

public:
	ASector7World();

protected:
	virtual void BeginPlay() override;

public:
	/** Time of day on alien planet in 24h format (e.g. 14.5 = 2:30 PM) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Sector7|Time")
	float PlanetaryTimeHours = 12.0f;

	/** Ratio of real seconds to in-game hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Sector7|Time")
	float SecondsPerInGameHour = 120.0f;

	/** Registered colony districts */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Exile|Sector7|Colony")
	TArray<TObjectPtr<ASector7District>> RegisteredDistricts;

	/** Active environmental control actor */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Exile|Sector7|Colony")
	TObjectPtr<ASector7Environment> EnvironmentManager;
};
