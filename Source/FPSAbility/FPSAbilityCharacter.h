// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Logging/LogMacros.h"
#include "FPSAbilityCharacter.generated.h"

class UGameplayAbility;
class UFPSA_GABase;
class UFPSA_PlayerWidget;
class UGameplayEffect;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UTP_WeaponComponent;
class UAbilitySystemComponent;
class UFPSA_AttributeSetBase;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game, Blueprintable)
class AFPSAbilityCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	/*----------------------------------------- MEMBERS -------------------------------------------------------*/
	
protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Ability System Component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UAbilitySystemComponent> m_AbilitySystemComponent;

	/** Attribute Set */
	UPROPERTY(VisibleAnywhere, Category = "AFPSAbilityCharacter")
	TObjectPtr<UFPSA_AttributeSetBase> m_AttributeSet;

	/** Initial Stats Effect */
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category = AbilitySystem)
	TSubclassOf<UGameplayEffect> m_InitStatsEffect;
	
	/** Weapon Component */
	UPROPERTY(VisibleAnywhere, Category = "AFPSAbilityCharacter")
	TObjectPtr<UTP_WeaponComponent> m_CurrentWeaponComponent;

	/** Weapon Component */
	UPROPERTY(VisibleAnywhere, Category = "AFPSAbilityCharacter")
	TArray<TObjectPtr<UTP_WeaponComponent>> m_AllWeaponComponents;

	UPROPERTY(EditAnywhere, Category = "Player Widget Class")
	TSubclassOf<UFPSA_PlayerWidget> m_PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Player Widget")
	TObjectPtr<UFPSA_PlayerWidget> m_PlayerWidget;

	UPROPERTY(EditAnywhere, Category = "AFPSAbilityCharacter")
	TSubclassOf<UGameplayAbility> m_AbilityPassiveManaRegen;

	FTimerHandle m_ManaRegenTimerHandle;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** SwitchWeapon Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponAction;
	
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool m_HaseRifle;
	
	/*----------------------------------------- FUNCTIONS -------------------------------------------------------*/
public:
	AFPSAbilityCharacter();

	bool CheckIfAlreadyHasWeapon(UTP_WeaponComponent* WeaponComponent);

	void AddWeaponComponent(UTP_WeaponComponent* WeaponComponent);
	
protected:
	virtual void BeginPlay();

	virtual  void Tick(float DeltaSeconds) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void RegenMana();

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void UseWeaponAbility(const FInputActionValue& Value);

	/** Switch the weapon */
	UFUNCTION()
	void SwitchWeapon(const FInputActionValue& Value);

	UFUNCTION()
	void ManageChangeWeapon(UTP_WeaponComponent* WeaponComponent);
	
	/*----------------------------------------- OVERRIDE -------------------------------------------------------*/
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	// End of APawn interface
	
	/*----------------------------------------- GET / SET -------------------------------------------------------*/
public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	FORCEINLINE void SetWeaponComponent(UTP_WeaponComponent* WeaponComponent) { m_CurrentWeaponComponent = WeaponComponent; }
	
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return m_AbilitySystemComponent; }
	
	FORCEINLINE bool GetHasRifle() const { return m_HaseRifle; }
	FORCEINLINE void SetHasRifle(bool bHaseRifle) { m_HaseRifle = bHaseRifle; }

	FORCEINLINE TObjectPtr<UFPSA_PlayerWidget> GetPlayerWidget() const { return m_PlayerWidget; }
};

