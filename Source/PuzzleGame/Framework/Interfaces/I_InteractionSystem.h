// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <PuzzleGame/Data/RPS_States.h>
#include "I_InteractionSystem.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UI_InteractionSystem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEGAME_API II_InteractionSystem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ERPS_States GetState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetState(ERPS_States curState);



	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginInteractionTimer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopInteractionTimer();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HighlightObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveHighlight();
};
