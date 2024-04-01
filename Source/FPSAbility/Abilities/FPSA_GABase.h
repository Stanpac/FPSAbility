// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FPSA_GABase.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class FPSABILITY_API UFPSA_GABase : public UGameplayAbility
{
	GENERATED_BODY()
	/* ----------------------------------------- MEMBERS ------------------------------------------------------- */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icon")
	UTexture2D* m_Icon;
	
	/* ----------------------------------------- FUNCTIONS -------------------------------------------------------*/
	
public:
	UFPSA_GABase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	FORCEINLINE UTexture2D* GetIcon() const { return m_Icon; }
};
