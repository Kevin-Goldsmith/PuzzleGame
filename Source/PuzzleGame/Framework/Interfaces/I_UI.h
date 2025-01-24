// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <PuzzleGame/Data/RPS_States.h>
#include "I_UI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UI_UI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEGAME_API II_UI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddElement(ERPS_States state);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateCounter(int curVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateMaxCounter(int curVal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateModCount(int curVal);
};
