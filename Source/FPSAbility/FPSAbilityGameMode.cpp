// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAbilityGameMode.h"
#include "FPSAbilityCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSAbilityGameMode::AFPSAbilityGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
