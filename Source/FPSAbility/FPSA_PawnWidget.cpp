// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSA_PawnWidget.h"

#include "Components/ProgressBar.h"

void UFPSA_PawnWidget::UpdateHealthBar(float M_Health, float M_MaxHealth)
{
	m_HealthBar->SetPercent(M_Health / M_MaxHealth);
}
