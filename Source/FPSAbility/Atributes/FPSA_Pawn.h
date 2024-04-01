// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSA_Pawn.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UFPSA_PawnWidget;
class UAbilitySystemComponent;
class UFPSA_AttributeSetBase;
class UGameplayEffect;
class UStaticMeshComponent;

UCLASS()
class FPSABILITY_API AFPSA_Pawn : public APawn
{
	GENERATED_BODY()
    /* ----------------------------------------- MEMBERS ------------------------------------------------------- */
protected:

	/** Ability System Component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAbilitySystemComponent> m_AbilitySystemComponent;

	/** Attribute Set */
	UPROPERTY(VisibleAnywhere, Category = "AFPSA_Pawn")
	TObjectPtr<UFPSA_AttributeSetBase> m_AttributeSet;

	/** Initial Stats Effect */
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category = AbilitySystem)
	TSubclassOf<UGameplayEffect> m_InitStatsEffect;

	UPROPERTY(EditAnywhere, Category = "AFPSA_Pawn")
	TObjectPtr<UWidgetComponent> m_WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "AFPSA_Pawn")
	TSubclassOf<UFPSA_PawnWidget> m_WidgetClass;

	UPROPERTY(EditAnywhere, Category = "AFPSA_Pawn")
	TObjectPtr<UStaticMeshComponent> m_StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "AFPSA_Pawn")
	TObjectPtr<UBoxComponent> m_BoxComponent;
	/* ----------------------------------------- FUNCTIONS ------------------------------------------------------- */
	
public:
	AFPSA_Pawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
