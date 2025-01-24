// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleGame/Framework/Interfaces/I_InteractionSystem.h"
#include "Camera/CameraComponent.h"
#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UInteractor : public UActorComponent, public II_InteractionSystem
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractor();
	AActor* hitActor;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMaterialInstance* m_Outline;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle timer_Interaction;

	FHitResult hitRes;

	

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BeginTrace();


	// Interface Events

	void BeginInteractionTimer_Implementation() override;
	
	void StopInteractionTimer_Implementation() override;
};
