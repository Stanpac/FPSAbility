// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSAbilityPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class FPSABILITY_API AFPSAbilityPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

protected:

	virtual void BeginPlay() override;

	virtual void AcknowledgePossession(APawn* P) override;
};
