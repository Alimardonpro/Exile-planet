// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Online/ExileOnlineTypes.h"
#include "ExileOnlineManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionStateChangedSignature, EExileSessionState, NewState);

/**
 * Subsystem placeholder for future multiplayer networking, colony server browsing, and player session handling.
 */
UCLASS()
class EXILEPLANET_API UExileOnlineManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Exile|Online")
	bool IsMultiplayerActive() const { return CurrentSessionState == EExileSessionState::InOnlineColony; }

	UFUNCTION(BlueprintPure, Category = "Exile|Online")
	EExileSessionState GetSessionState() const { return CurrentSessionState; }

	UFUNCTION(BlueprintPure, Category = "Exile|Online")
	const FExilePlayerSessionInfo& GetCurrentSessionInfo() const { return CurrentSession; }

	UPROPERTY(BlueprintAssignable, Category = "Exile|Online")
	FOnSessionStateChangedSignature OnSessionStateChanged;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Online")
	EExileSessionState CurrentSessionState = EExileSessionState::OfflineSingleplayer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Exile|Online")
	FExilePlayerSessionInfo CurrentSession;
};
