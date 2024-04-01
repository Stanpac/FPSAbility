// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSA_AttributeSetBase.h"
#include "GameplayEffectExtension.h"

#include "Net/UnrealNetwork.h"

UFPSA_AttributeSetBase::UFPSA_AttributeSetBase()
{
}

void UFPSA_AttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UFPSA_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSA_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSA_AttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSA_AttributeSetBase, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSA_AttributeSetBase, Damage, COND_None, REPNOTIFY_Always);
}

void UFPSA_AttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSA_AttributeSetBase, Health, OldValue);
}

void UFPSA_AttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSA_AttributeSetBase, MaxHealth, OldValue);
}

void UFPSA_AttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSA_AttributeSetBase, Mana, OldValue);
}

void UFPSA_AttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSA_AttributeSetBase, MaxMana, OldValue);
}

void UFPSA_AttributeSetBase::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSA_AttributeSetBase, Damage, OldValue);
}

void UFPSA_AttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if(Data.EvaluatedData.Attribute == GetManaAttribute()) {
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}
