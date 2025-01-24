// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Framework/Interfaces/I_UI.h"
#include <Framework/Interfaces/I_Cubes.h>
#include "Framework/UI/W_HUD.h"
#include "PuzzleGamePlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class PUZZLEGAME_API APuzzleGamePlayerController : public APlayerController, public II_Cubes, public II_UI
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UUserWidget* ref_HUD;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UUserWidget> class_HUD;


	UFUNCTION()
	void ShowHUD(bool show);

	void AddElementToUI_Implementation(ERPS_States state) override;

	void UpdateCounterVal_Implementation(int curVal) override;

	void UpdateMaxMatches_Implementation(int curVal) override;

	void UpdateMod_Implementation(int curVal) override;

};
