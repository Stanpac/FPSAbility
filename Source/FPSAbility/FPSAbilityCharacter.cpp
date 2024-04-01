// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAbilityCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSA_PlayerWidget.h"
#include "InputActionValue.h"
#include "Abilities/FPSA_GABase.h"
#include "TP_WeaponComponent.h"
#include "Atributes/FPSA_AttributeSetBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFPSAbilityCharacter

AFPSAbilityCharacter::AFPSAbilityCharacter()
{
	// Character doesnt have a rifle at start
	m_HaseRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	m_AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	m_AbilitySystemComponent->SetIsReplicated(true);

	m_AttributeSet = CreateDefaultSubobject<UFPSA_AttributeSetBase>(TEXT("AttributeSet"));
	
	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;
}

bool AFPSAbilityCharacter::CheckIfAlreadyHasWeapon(UTP_WeaponComponent* WeaponComponent)
{
	for (UTP_WeaponComponent* Weapon : m_AllWeaponComponents) {
		if (Weapon == WeaponComponent) {
			return true;
		}
	}
	return false;
}

void AFPSAbilityCharacter::AddWeaponComponent(UTP_WeaponComponent* WeaponComponent)
{
	m_AllWeaponComponents.Add(WeaponComponent);
}

void AFPSAbilityCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Init Player Start
	m_AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(m_InitStatsEffect, 1.0f, m_AbilitySystemComponent->MakeEffectContext());

	if (m_PlayerWidgetClass) {
		m_PlayerWidget = CreateWidget<UFPSA_PlayerWidget>(GetWorld(), m_PlayerWidgetClass);
		if (m_PlayerWidget) {
			m_PlayerWidget->AddToViewport();
		}
	}
	m_AbilitySystemComponent->K2_GiveAbility(m_AbilityPassiveManaRegen);
}

void AFPSAbilityCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (m_PlayerWidget) {
		m_PlayerWidget->UpdateHealthBar(m_AttributeSet->GetHealth(), m_AttributeSet->GetMaxHealth());
		m_PlayerWidget->UpdateManaBar(m_AttributeSet->GetMana(), m_AttributeSet->GetMaxMana());
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPSAbilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSAbilityCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSAbilityCharacter::Look);

		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AFPSAbilityCharacter::UseWeaponAbility);

		// Switching Weapons
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &AFPSAbilityCharacter::SwitchWeapon);
		
	} else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFPSAbilityCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (m_AbilitySystemComponent) {
		m_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
	SetOwner(NewController);
}


void AFPSAbilityCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSAbilityCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSAbilityCharacter::UseWeaponAbility(const FInputActionValue& Value)
{
	if (!IsValid(m_CurrentWeaponComponent) || m_AllWeaponComponents.Num() <= 0){
		return;
	}
	
	GetAbilitySystemComponent()->TryActivateAbilityByClass(m_CurrentWeaponComponent->GetAbilityToUse());

	if (m_AttributeSet->GetMana() < m_AttributeSet->GetMaxMana() && !GetWorld()->GetTimerManager().IsTimerActive(m_ManaRegenTimerHandle)) {
		GetWorld()->GetTimerManager().SetTimer(m_ManaRegenTimerHandle, this, &AFPSAbilityCharacter::RegenMana, 0.1f, true);
	}
}

void AFPSAbilityCharacter::RegenMana()
{
	if (m_AttributeSet->GetMana() < m_AttributeSet->GetMaxMana()) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(m_AbilityPassiveManaRegen);
	} else {
		GetWorld()->GetTimerManager().ClearTimer(m_ManaRegenTimerHandle);
	}
}
void AFPSAbilityCharacter::SwitchWeapon(const FInputActionValue& Value)
{
	if (m_AllWeaponComponents.Num() <= 1) {
		return;
	}

	float SwitchValue = Value.Get<float>();
	
	float CurrentIndex = m_AllWeaponComponents.Find(m_CurrentWeaponComponent);
	if (SwitchValue > 0) {
		CurrentIndex++;
		if (CurrentIndex >= m_AllWeaponComponents.Num()) {
			CurrentIndex = 0;
		}
		ManageChangeWeapon(m_AllWeaponComponents[CurrentIndex]);
	} else if (SwitchValue < 0) {
		CurrentIndex--;
		if (CurrentIndex < 0) {
			CurrentIndex = m_AllWeaponComponents.Num() - 1;
		}
		ManageChangeWeapon(m_AllWeaponComponents[CurrentIndex]);
	}
}

void AFPSAbilityCharacter::ManageChangeWeapon(UTP_WeaponComponent* WeaponComponent)
{
	m_CurrentWeaponComponent->SetVisibility(false);
	m_CurrentWeaponComponent = WeaponComponent;
	m_CurrentWeaponComponent->SetVisibility(true);
	m_PlayerWidget->GetAbilityIcon()->SetBrushFromTexture(WeaponComponent->GetAbilityToUse().GetDefaultObject()->GetIcon());
}
