// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExileGameMode.generated.h"

/**
 * Foundation GameMode for Exile Planet.
 * Configures core default gameplay classes without bloated, monolithic logic.
 */
UCLASS()
class EXILEPLANET_API AExileGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExileGameMode();
};
