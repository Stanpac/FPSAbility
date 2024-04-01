// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSA_PlayerWidget.h"

#include "Components/ProgressBar.h"

void UFPSA_PlayerWidget::UpdateHealthBar(float M_Health, float M_MaxHealth)
{
	m_HealthBar->SetPercent(M_Health / M_MaxHealth);
}

void UFPSA_PlayerWidget::UpdateManaBar(float M_Mana, float M_MaxMana)
{
	m_ManaBar->SetPercent(M_Mana / M_MaxMana);
}
