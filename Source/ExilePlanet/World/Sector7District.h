// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector7District.generated.h"

UENUM(BlueprintType)
enum class ESector7DistrictType : uint8
{
	LandingPort UMETA(DisplayName = "Landing Port & Hangar"),
	RefineryFacility UMETA(DisplayName = "Ore Processing Refinery"),
	ExcavationQuarry UMETA(DisplayName = "Excavation & Mining Quarry"),
	PenalBarracks UMETA(DisplayName = "Prisoner Penal Quarters"),
	HighSecurityGate UMETA(DisplayName = "Security Checkpoint")
};

/**
 * Defines a regional district within Sector 7.
 */
UCLASS()
class EXILEPLANET_API ASector7District : public AActor
{
	GENERATED_BODY()

public:
	ASector7District();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|District")
	FName DistrictID = TEXT("District_LandingPort");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|District")
	FText DistrictName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|District")
	ESector7DistrictType DistrictType = ESector7DistrictType::LandingPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|District")
	float HazardRating = 1.0f; // Scale 1.0 - 5.0
};
