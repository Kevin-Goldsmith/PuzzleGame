// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"
#include "Kismet/KismetMathLibrary.h"

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
	FRotator startRot;
	FVector startTrace;
	GetOwner()->GetActorEyesViewPoint(startTrace, startRot);

	FVector endTrace;
	endTrace = startTrace + (UKismetMathLibrary::GetForwardVector(startRot) * 1000.f);
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.bTraceComplex;
	

	GetWorld()->LineTraceSingleByChannel(hitRes, 
											startTrace, 
											endTrace, 
											ECollisionChannel::ECC_Visibility,
											Params,
											FCollisionResponseParams::DefaultResponseParam);

	//DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Red, false, 2, 0, 2);
	if (hitRes.bBlockingHit)
	{
		if (hitActor != hitRes.GetActor())
		{
			if (hitActor)
			{
				if (II_InteractionSystem* Interact = Cast<II_InteractionSystem>(hitActor))
				{
					II_InteractionSystem::Execute_RemoveHighlight(hitActor);
					hitActor = nullptr;
				}
			}

			hitActor = hitRes.GetActor();

			if (II_InteractionSystem* Interact = Cast<II_InteractionSystem>(hitActor))
			{
				II_InteractionSystem::Execute_HighlightObject(hitActor);
				hitActor->GetComponentByClass<UStaticMeshComponent>()->SetOverlayMaterial(m_Outline);
			}
		}
	}
	else
	{
		if (hitActor)
		{
			if (II_InteractionSystem* Interact = Cast<II_InteractionSystem>(hitActor))
			{
				II_InteractionSystem::Execute_RemoveHighlight(hitActor);
				hitActor = nullptr;
			}
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
