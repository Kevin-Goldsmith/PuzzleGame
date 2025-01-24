// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <PuzzleGame/Data/RPS_States.h>
#include "I_States.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_States : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEGAME_API II_States
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ERPS_States GetState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetState(ERPS_States curState);

};
