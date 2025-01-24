// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include <PuzzleGame/Framework/Interfaces/I_Cubes.h>
#include "PuzzleGame/Character/Interactor.h"
#include "PuzzleGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class UInteractor;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APuzzleGameCharacter : public ACharacter, public II_InteractionSystem
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RTS_ToggleAction;

	
public:
	APuzzleGameCharacter();



	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Input)
	UInputMappingContext* IMC_locomotion;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Input)
	UInputMappingContext* IMC_RTS;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMaterialInstance* m_Overlay;

protected:
	virtual void BeginPlay();

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	UInteractor* InteractorComp;

	UInputComponent* inputComp;


public:
	

protected:

	// INPUT //
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);
	void RTS_Toggle(const FInputActionValue& Value);




protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UInputMappingContext* oldMap = nullptr;

	UInputMappingContext* newMap = IMC_locomotion;


public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	AActor* RTS_Master_Ref;

	bool isRTS;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftClassPtr<AActor> masterCube_Ref;


	UFUNCTION(BlueprintImplementableEvent)
	void SpawnAndAttMasterCube();

	// INTERFACE EVENTS //

};

