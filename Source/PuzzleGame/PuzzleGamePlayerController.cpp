// Copyright Epic Games, Inc. All Rights Reserved.


#include "PuzzleGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

void APuzzleGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	ShowHUD(true);
}

void APuzzleGamePlayerController::ShowHUD(bool show)
{
	if (!ref_HUD)
	{
		ref_HUD = CreateWidget<UUserWidget>(this, class_HUD);
	}

	if (show)
	{
		ref_HUD->AddToViewport(0);
	}
	else
	{
		ref_HUD->RemoveFromParent();
	}
}

void APuzzleGamePlayerController::AddElementToUI_Implementation(ERPS_States state)
{
	if (ref_HUD == nullptr)
	{
		return;
	}

	if (ref_HUD->GetClass()->ImplementsInterface(UI_UI::StaticClass()))
	{
		II_UI::Execute_AddElement(ref_HUD, state);
	}
}

void APuzzleGamePlayerController::UpdateCounterVal_Implementation(int curVal)
{
	if (ref_HUD->GetClass()->ImplementsInterface(UI_UI::StaticClass()))
	{
		II_UI::Execute_UpdateCounter(ref_HUD, curVal);
	}
}

void APuzzleGamePlayerController::UpdateMaxMatches_Implementation(int curVal)
{
	if (ref_HUD->GetClass()->ImplementsInterface(UI_UI::StaticClass()))
	{
		II_UI::Execute_UpdateMaxCounter(ref_HUD, curVal);
	}
}

void APuzzleGamePlayerController::UpdateMod_Implementation(int curVal)
{
	if (ref_HUD->GetClass()->ImplementsInterface(UI_UI::StaticClass()))
	{
		II_UI::Execute_UpdateModCount(ref_HUD, curVal);
	}
}

	