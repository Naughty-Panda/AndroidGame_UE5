// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidGameGameMode.h"
#include "AndroidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MobileHUD.h"

AAndroidGameGameMode::AAndroidGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default HUD class to our MobileHUD.cpp
	HUDClass = AMobileHUD::StaticClass();
}
