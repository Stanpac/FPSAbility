// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class UFPSA_GABase;
class UImage;
class AFPSAbilityCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSABILITY_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	/* ----------------------------------------- MEMBERS ------------------------------------------------------- */
protected:
	/** The Character holding this weapon*/
	TObjectPtr<AFPSAbilityCharacter> Character;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Ability to use */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, DisplayName = "Ability To Use")
	TSubclassOf<UFPSA_GABase> m_AbilityToUse;
	
	/* ----------------------------------------- FUNCTIONS -------------------------------------------------------*/
public:
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPSAbilityCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void UseAbility();

	/* ----------------------------------------- GET / SET -------------------------------------------------------*/
	
	FORCEINLINE TSubclassOf<UFPSA_GABase> GetAbilityToUse() const { return m_AbilityToUse; }
};
