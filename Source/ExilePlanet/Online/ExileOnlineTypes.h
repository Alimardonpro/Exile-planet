// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExileOnlineTypes.generated.h"

/** Online session connectivity state for future multiplayer */
UENUM(BlueprintType)
enum class EExileSessionState : uint8
{
	OfflineSingleplayer UMETA(DisplayName = "Offline Singleplayer"),
	ConnectingToColonyServer UMETA(DisplayName = "Connecting To Colony Server"),
	InOnlineColony UMETA(DisplayName = "Active In Online Colony"),
	Disconnected UMETA(DisplayName = "Disconnected")
};

/** Network session metadata prepared for future Unreal replication and sessions */
USTRUCT(BlueprintType)
struct FExilePlayerSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Online")
	FString SessionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Online")
	FString ServerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Online")
	int32 MaxConvicts = 32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Online")
	int32 CurrentConvicts = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exile|Online")
	int32 PingMs = 0;
};
