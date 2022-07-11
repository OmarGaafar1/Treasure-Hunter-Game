// Copyright Epic Games, Inc. All Rights Reserved.

#include "TreasureHunterGameMode.h"
#include "TreasureHunterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATreasureHunterGameMode::ATreasureHunterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
