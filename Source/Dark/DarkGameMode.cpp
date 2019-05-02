// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DarkGameMode.h"
#include "DarkHUD.h"
#include "DarkCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADarkGameMode::ADarkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADarkHUD::StaticClass();
}
