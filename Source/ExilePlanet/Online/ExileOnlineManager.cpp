// Copyright Exile Planet. All Rights Reserved.

#include "Online/ExileOnlineManager.h"

void UExileOnlineManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSessionState = EExileSessionState::OfflineSingleplayer;
	CurrentSession.SessionID = TEXT("LOCAL_SESSION_01");
	CurrentSession.ServerName = TEXT("Exile Planet - Sector 7 Local");
	CurrentSession.MaxConvicts = 1;
	CurrentSession.CurrentConvicts = 1;
	CurrentSession.PingMs = 0;
}

void UExileOnlineManager::Deinitialize()
{
	Super::Deinitialize();
}
