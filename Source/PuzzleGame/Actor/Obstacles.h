// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "PuzzleGame/Framework/Interfaces/I_States.h"
#include "PuzzleGame/Framework/Interfaces/I_InteractionSystem.h"
#include "Obstacles.generated.h"

UCLASS()
class PUZZLEGAME_API AObstacles : public AActor, public II_States, public II_InteractionSystem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERPS_States curState = ERPS_States::Neutral;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UStaticMeshComponent* _Mesh;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USceneComponent* _Root;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBoxComponent* _Box;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateResult();

	ERPS_States GetState_Implementation() override;

	void SetState_Implementation(ERPS_States curState) override;

	void EnterTrigger(UPrimitiveComponent* selfComp, 
							AActor* otherActor, 
							UPrimitiveComponent* otherComp, 
							int num, 
							bool bSweep, 
							const FHitResult& hit);

};
