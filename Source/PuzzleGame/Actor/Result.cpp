// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Result.h"

// Sets default values
AResult::AResult()
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
void AResult::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResult::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ERPS_States AResult::GetState_Implementation()
{
	return ERPS_States(curState);
}

void AResult::SetState_Implementation(ERPS_States state)
{
	curState = state;
	UpdateResult();
}

void AResult::HighlightObject_Implementation()
{
	_Mesh->SetRenderCustomDepth(true);
	_Mesh->SetCustomDepthStencilValue(1);
}

void AResult::RemoveHighlight_Implementation()
{
	_Mesh->SetRenderCustomDepth(false);
	_Mesh->SetCustomDepthStencilValue(0);
	_Mesh->SetOverlayMaterial(NULL);
}


