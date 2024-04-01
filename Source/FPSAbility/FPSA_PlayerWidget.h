// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSA_PlayerWidget.generated.h"

class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class FPSABILITY_API UFPSA_PlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	/* ----------------------------------------- MEMBERS ------------------------------------------------------- */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* m_HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* m_ManaBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* m_AbilityIcon;
	/* ----------------------------------------- FUNCTIONS -------------------------------------------------------*/
public:
	void UpdateHealthBar(float M_Health, float M_MaxHealth);
	void UpdateManaBar(float M_Mana, float M_MaxMana);
	/* ----------------------------------------- GET / SET -------------------------------------------------------*/
	FORCEINLINE UProgressBar* GetHealthBar() const { return m_HealthBar; }
	FORCEINLINE UProgressBar* GetManaBar() const { return m_ManaBar; }
	
	FORCEINLINE UImage* GetAbilityIcon() const { return m_AbilityIcon; }
	FORCEINLINE void SetAbilityIcon(UImage* M_AbilityIcon) { m_AbilityIcon = M_AbilityIcon; }
};
