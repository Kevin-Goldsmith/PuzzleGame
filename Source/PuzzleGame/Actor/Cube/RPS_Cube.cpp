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
	_Box->SetHiddenInGame(false);

	_Name = CreateDefaultSubobject<UTextRenderComponent>("Name");
	_Name->SetupAttachment(_Root);
	_Name->SetRelativeLocation(FVector(0, 0, 20));
	_Name->SetRelativeRotation(FRotator(0, 0, 0));
	_Name->SetHorizontalAlignment(EHTA_Center);
	_Name->SetVerticalAlignment(EVRTA_TextCenter);
	_Name->SetWorldSize(12.f);
}

// Called when the game starts or when spawned
void ARPS_Cube::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle wait;
	GetWorld()->GetTimerManager().SetTimer(wait, this, &ARPS_Cube::UpdateNames, 2, false);
}

void ARPS_Cube::UpdateNames()
{
	switch (curState)
	{
	case ERPS_States::Rock:
		_Name->SetText(FText::FromString(TEXT("Rock")));
		break;

	case ERPS_States::Paper:
		_Name->SetText(FText::FromString(TEXT("Paper")));
		break;

	case ERPS_States::Scissors:
		_Name->SetText(FText::FromString(TEXT("Scissor")));
		break;
	}
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
	_Mesh->SetCustomDepthStencilValue(1);
}

void ARPS_Cube::RemoveHighlight_Implementation()
{
	_Mesh->SetRenderCustomDepth(false);
	_Mesh->SetCustomDepthStencilValue(0);
	_Mesh->SetOverlayMaterial(NULL);
}

void ARPS_Cube::InteractWithObject_Implementation()
{
	AActor* parentActor;
	parentActor = GetAttachParentActor();

	if (parentActor)
	{
		if (II_Cubes* Interact = Cast<II_Cubes>(parentActor))
		{
			II_Cubes::Execute_PressedButton(parentActor, curState);
		}
	}
}

