// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include <Components/TextRenderComponent.h>
#include <PuzzleGame/Data/RPS_States.h>
#include "PuzzleGame/Framework/Interfaces/I_Cubes.h"
#include "PuzzleGame/Framework/Interfaces/I_States.h"
#include "PuzzleGame/Framework/Interfaces/I_InteractionSystem.h"
#include "RPS_Cube.generated.h"



class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;


UCLASS(Abstract)
class PUZZLEGAME_API ARPS_Cube : public AActor, public II_InteractionSystem, public II_States
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPS_Cube();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERPS_States curState = ERPS_States::Neutral;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	USceneComponent* _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* _Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* _Box;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UTextRenderComponent* _Name;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void UpdateNames();


	// Interface Events //

	ERPS_States GetState_Implementation() override;

	void SetState_Implementation(ERPS_States curState) override;

	void HighlightObject_Implementation() override;
	
	void RemoveHighlight_Implementation() override;

	void InteractWithObject_Implementation() override;

};
