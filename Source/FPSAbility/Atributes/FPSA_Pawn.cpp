// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSA_Pawn.h"

#include "AbilitySystemComponent.h"
#include "FPSA_AttributeSetBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "FPSAbility/FPSA_PawnWidget.h"



AFPSA_Pawn::AFPSA_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;

	m_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = m_BoxComponent;
	
	m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	m_StaticMeshComponent->SetupAttachment(RootComponent);
	
	m_AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	m_AbilitySystemComponent->SetIsReplicated(true);

	m_AttributeSet = CreateDefaultSubobject<UFPSA_AttributeSetBase>(TEXT("AttributeSet"));
	
	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;

	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	m_WidgetComponent->SetupAttachment(RootComponent);
}

void AFPSA_Pawn::BeginPlay()
{
	Super::BeginPlay();
	// Init Player Start
	m_AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(m_InitStatsEffect, 1.0f, m_AbilitySystemComponent->MakeEffectContext());
}

void AFPSA_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_WidgetComponent) {
		Cast<UFPSA_PawnWidget>(m_WidgetComponent->GetWidget())->UpdateHealthBar(m_AttributeSet->GetHealth(), m_AttributeSet->GetMaxHealth());
	}
}

void AFPSA_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

