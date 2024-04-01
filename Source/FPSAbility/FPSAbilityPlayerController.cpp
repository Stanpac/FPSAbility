// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSAbilityPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSAbilityCharacter.h"

void AFPSAbilityPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void AFPSAbilityPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	AFPSAbilityCharacter* CharacterBase = Cast<AFPSAbilityCharacter>(P);
	
	if (CharacterBase) {
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}
}
