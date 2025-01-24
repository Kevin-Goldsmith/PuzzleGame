// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleGameCharacter.h"
#include "PuzzleGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APuzzleGameCharacter

APuzzleGameCharacter::APuzzleGameCharacter()
{
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
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InteractorComp = CreateDefaultSubobject<UInteractor>("Interactor");

}

void APuzzleGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (II_InteractionSystem* interact = Cast<II_InteractionSystem>(InteractorComp))
	{
		II_InteractionSystem::Execute_BeginInteractionTimer(InteractorComp);
	}

	SpawnAndAttMasterCube();

	InteractorComp->m_Outline = m_Overlay;
}

//////////////////////////////////////////////////////////////////////////// Input

void APuzzleGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	inputComp = PlayerInputComponent;

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APuzzleGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APuzzleGameCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APuzzleGameCharacter::Interact);

		EnhancedInputComponent->BindAction(RTS_ToggleAction, ETriggerEvent::Started, this, &APuzzleGameCharacter::RTS_Toggle);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APuzzleGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APuzzleGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APuzzleGameCharacter::Interact(const FInputActionValue& Value)
{
	AActor* hitAct = InteractorComp->hitActor;
	
	if(IsValid(hitAct))
	{
		if (II_InteractionSystem* interact = Cast<II_InteractionSystem>(hitAct))
		{
			II_InteractionSystem::Execute_InteractWithObject(hitAct);	
		}
	}
}

void APuzzleGameCharacter::RTS_Toggle(const FInputActionValue& Value)
{
	if (!IsValid(RTS_Master_Ref))
	{
		return;
	}

	isRTS = RTS_Master_Ref->IsHidden();

	if (II_Cubes* cube = Cast<II_Cubes>(RTS_Master_Ref))
	{
		II_Cubes::Execute_ToggleVisibility(RTS_Master_Ref, isRTS);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf(TEXT("%s"), isRTS ? TEXT("true") : TEXT("false")));

	if (inputComp)
	{
		if (UEnhancedInputComponent* tempComp = Cast<UEnhancedInputComponent>(inputComp))
		{
			oldMap = newMap;
			newMap = isRTS ? IMC_RTS : IMC_locomotion;
			
			if (APlayerController* playerCont = Cast<APlayerController>(GetController()))
			{
				if (UEnhancedInputLocalPlayerSubsystem* subsystem =
					ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCont->GetLocalPlayer()))
				{
					subsystem->AddMappingContext(newMap, 0);
				
					if (oldMap)
					{
						subsystem->RemoveMappingContext(oldMap);
					}
				}
			}
		}
	}


	if (isRTS)
	{
		RTS_Master_Ref->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		RTS_Master_Ref->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RTS_Master_Ref->SetActorRelativeLocation(FVector(150, 0, 0));
	}
}
