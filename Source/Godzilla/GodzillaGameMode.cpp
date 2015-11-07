// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Godzilla.h"
#include "GodzillaGameMode.h"
#include "GodzillaCharacter.h"

AGodzillaGameMode::AGodzillaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Godzilla/Blueprints/GodzillaCharacter"));
	if (PlayerPawnBPClass.Class == NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
