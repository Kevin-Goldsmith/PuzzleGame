// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	
	
	
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractor::BeginTrace()
{

	UCameraComponent* camComp;
	camComp = GetOwner()->GetComponentByClass<UCameraComponent>();

	FVector startTrace;
	startTrace = camComp->GetComponentLocation();

	FVector endTrace;
	endTrace = camComp->GetForwardVector() * 1000.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	

	GetWorld()->LineTraceSingleByChannel(hitRes, 
											startTrace, 
											endTrace, 
											ECollisionChannel::ECC_Camera,
											Params,
											FCollisionResponseParams::DefaultResponseParam);

	if (hitRes.bBlockingHit)
	{
		hitActor = hitRes.GetActor();

		if (II_InteractionSystem* Interact = Cast<II_InteractionSystem>(hitActor))
		{
			II_InteractionSystem::Execute_HighlightObject(hitActor);
		}
	}
	else
	{
		if (II_InteractionSystem* Interact = Cast<II_InteractionSystem>(hitRes.GetActor()))
		{
			II_InteractionSystem::Execute_RemoveHighlight(hitActor);
			hitActor = nullptr;
		}
		
	}


}

void UInteractor::BeginInteractionTimer_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(timer_Interaction, this, &UInteractor::BeginTrace, 0.1, true);
}

void UInteractor::StopInteractionTimer_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(timer_Interaction);
}
