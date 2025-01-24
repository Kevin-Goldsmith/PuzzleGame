// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Obstacles.h"

// Sets default values
AObstacles::AObstacles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	_Mesh->SetupAttachment(_Root);

	_Box = CreateDefaultSubobject<UBoxComponent>("Box");
	_Box->SetupAttachment(_Root);
}

// Called when the game starts or when spawned
void AObstacles::BeginPlay()
{
	Super::BeginPlay();

	_Box->OnComponentBeginOverlap.AddDynamic(this, &AObstacles::EnterTrigger);	
}

// Called every frame
void AObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ERPS_States AObstacles::GetState_Implementation()
{
	return ERPS_States(curState);
}

void AObstacles::SetState_Implementation(ERPS_States state)
{
	curState = state;
}

void AObstacles::EnterTrigger(UPrimitiveComponent* selfComp, AActor* otherActor, UPrimitiveComponent* otherComp, int num, bool bSweep, const FHitResult& hit)
{
	if (II_States* state = Cast<II_States>(otherActor))
	{
		if (curState == II_States::Execute_GetState(otherActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, ("Successfully dealt with Obstacle"));
		}
	}
}

