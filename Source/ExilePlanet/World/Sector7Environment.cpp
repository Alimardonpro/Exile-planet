// Copyright Exile Planet. All Rights Reserved.

#include "World/Sector7Environment.h"

ASector7Environment::ASector7Environment()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASector7Environment::SetWeatherState(EPlanetaryWeatherState NewState)
{
	CurrentWeather = NewState;
}
