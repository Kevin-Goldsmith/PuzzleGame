// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <PuzzleGame/Data/RPS_States.h>
#include "I_Cubes.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Cubes : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEGAME_API II_Cubes
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PressedButton(ERPS_States state);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleVisibility(bool val);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddElementToUI(ERPS_States state);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateCounterVal(int val);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateMaxMatches(int val);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateMod(int val);


};
