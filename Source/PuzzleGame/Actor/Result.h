// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "PuzzleGame/Framework/Interfaces/I_States.h"
#include "PuzzleGame/Framework/Interfaces/I_InteractionSystem.h"
#include "Result.generated.h"

UCLASS()
class PUZZLEGAME_API AResult : public AActor, public II_States, public II_InteractionSystem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResult();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	ERPS_States curState = ERPS_States::Neutral;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UStaticMeshComponent* _Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USceneComponent* _Root;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBoxComponent* _Box;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateResult();

	ERPS_States GetState_Implementation() override;

	void SetState_Implementation(ERPS_States curState) override;


	void HighlightObject_Implementation() override;

	void RemoveHighlight_Implementation() override;
};
