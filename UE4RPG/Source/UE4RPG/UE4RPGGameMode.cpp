// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4RPGGameMode.h"
#include "UE4RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4RPGGameMode::AUE4RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
