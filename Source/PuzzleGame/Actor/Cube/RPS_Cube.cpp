// Fill out your copyright notice in the Description page of Project Settings.


#include "RPS_Cube.h"

// Sets default values
ARPS_Cube::ARPS_Cube()
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
void ARPS_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPS_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ERPS_States ARPS_Cube::GetState_Implementation()
{
	return curState;
}

void ARPS_Cube::SetState_Implementation(ERPS_States state)
{
	curState = state;
}

void ARPS_Cube::HighlightObject_Implementation()
{
	_Mesh->SetRenderCustomDepth(true);
}

void ARPS_Cube::RemoveHighlight_Implementation()
{
	_Mesh->SetRenderCustomDepth(false);
}

