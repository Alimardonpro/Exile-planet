// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector7Environment.generated.h"

/** Planetary weather conditions */
UENUM(BlueprintType)
enum class EPlanetaryWeatherState : uint8
{
	ClearSkies UMETA(DisplayName = "Clear / Thin Atmosphere"),
	DustStorm UMETA(DisplayName = "Heavy Dust Storm"),
	AcidicRain UMETA(DisplayName = "Acidic Precipitation"),
	ElectromagneticTurbulence UMETA(DisplayName = "Electromagnetic Surge")
};

/**
 * Planetary atmosphere and environmental hazard system for Sector 7.
 */
UCLASS()
class EXILEPLANET_API ASector7Environment : public AActor
{
	GENERATED_BODY()

public:
	ASector7Environment();

	UFUNCTION(BlueprintCallable, Category = "Exile|Environment")
	void SetWeatherState(EPlanetaryWeatherState NewState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Environment")
	EPlanetaryWeatherState CurrentWeather = EPlanetaryWeatherState::ClearSkies;

	/** Outside toxicity level (0.0 = safe, 1.0 = lethal without life support) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Environment")
	float AtmosphericToxicity = 0.35f;

	/** Surface gravity multiplier compared to Earth (1.0 = Earth normal) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Environment")
	float PlanetaryGravityRatio = 0.92f;
};
