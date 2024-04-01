// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "FPSA_AttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *  Base class for all attribute sets in the game
 */
UCLASS()
class FPSABILITY_API UFPSA_AttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	/*----------------------------------------- MEMBERS -------------------------------------------------------*/
public:
	ATTRIBUTE_ACCESSORS(UFPSA_AttributeSetBase, Health);
	ATTRIBUTE_ACCESSORS(UFPSA_AttributeSetBase, MaxHealth);
	ATTRIBUTE_ACCESSORS(UFPSA_AttributeSetBase, Mana);
	ATTRIBUTE_ACCESSORS(UFPSA_AttributeSetBase, MaxMana);
	ATTRIBUTE_ACCESSORS(UFPSA_AttributeSetBase, Damage);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "FPSA|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "FPSA|MaxHealth", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "FPSA|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "FPSA|MaxMana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category = "FPSA|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
	
	/*----------------------------------------- FUNCTIONS -------------------------------------------------------*/
public:
	UFPSA_AttributeSetBase();

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldValue);

	/*----------------------------------------- OVERRIDE -------------------------------------------------------*/

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

};
