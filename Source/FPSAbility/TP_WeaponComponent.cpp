// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"

#include "AbilitySystemComponent.h"
#include "FPSAbilityCharacter.h"
#include "FPSA_PlayerWidget.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Abilities/FPSA_GABase.h"
#include "Components/Image.h"

UTP_WeaponComponent::UTP_WeaponComponent()
{
	// constructor
}

void UTP_WeaponComponent::UseAbility()
{
	if (Character == nullptr || Character->GetController() == nullptr) {
		return;
	}
	
	// Use Ability
	if (m_AbilityToUse != nullptr) {
		if (!Character->GetAbilitySystemComponent()->TryActivateAbilityByClass(m_AbilityToUse)) {
			return;
		};
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr) {
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::AttachWeapon(AFPSAbilityCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid
	if (Character == nullptr && Character->CheckIfAlreadyHasWeapon(this)){
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	Character->SetWeaponComponent(this);
	Character->AddWeaponComponent(this);
	
	if (m_AbilityToUse != nullptr) {
		Character->GetAbilitySystemComponent()->K2_GiveAbility(m_AbilityToUse);
		Character->GetPlayerWidget()->GetAbilityIcon()->SetBrushFromTexture(m_AbilityToUse.GetDefaultObject()->GetIcon());
	}
}
