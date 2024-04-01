// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSA_PawnWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSABILITY_API UFPSA_PawnWidget : public UUserWidget
{
	GENERATED_BODY()

	/* ----------------------------------------- MEMBERS ------------------------------------------------------- */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* m_HealthBar;
	
	/* ----------------------------------------- FUNCTIONS -------------------------------------------------------*/
public:
	void UpdateHealthBar(float M_Health, float M_MaxHealth);
};
