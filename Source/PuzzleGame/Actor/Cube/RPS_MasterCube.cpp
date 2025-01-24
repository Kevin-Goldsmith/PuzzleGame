


#include "RPS_MasterCube.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARPS_MasterCube::ARPS_MasterCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);

	_Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	_Billboard->SetupAttachment(_Root);
	_Billboard->SetRelativeLocation(FVector(0, 0, 10));
}

// Called when the game starts or when spawned
void ARPS_MasterCube::BeginPlay()
{
	Super::BeginPlay();

	SpawnCubes();

	playerXP = 1;
	MaxMatches = 2;

	playerCont = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (II_Cubes* cube = Cast<II_Cubes>(playerCont))
	{
		II_Cubes::Execute_UpdateMod(playerCont, playerXP);
	}
}

// Called every frame
void ARPS_MasterCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPS_MasterCube::SpawnCubes()
{
	for (int i = 0; i < 3; i++)
	{
		FActorSpawnParameters Params;

		FVector spawnOffset[] = { FVector(0, 0, 10), 
									FVector(-20, 70, 10), 
									FVector(-20, -70, 10)};
		
		FTransform spawnTransf;
		spawnTransf.SetLocation(GetActorLocation() + spawnOffset[i]);

		curCube = GetWorld()->SpawnActor<ARPS_Cube>(cubeClass, spawnTransf, Params);
		curCube->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

		curCube->SetActorLocation(GetActorLocation() + spawnOffset[i]);
		curCube->SetActorRotation(FRotator(0, 180, 0));

		ERPS_States tempState = static_cast<ERPS_States>((i % 3) + 1);
		curCube->curState = tempState;
		allCubes.Add(curCube);
	}
	curCube = nullptr;
}



void ARPS_MasterCube::PressedButton_Implementation(ERPS_States state)
{
	curState = state;
	//CheckElements();

	AddElement();
}

void ARPS_MasterCube::ToggleVisibility_Implementation(bool visible)
{
	SetActorHiddenInGame(!visible);

	for (ARPS_Cube* cube : allCubes)
	{
		cube->SetActorHiddenInGame(!visible);
		cube->SetActorEnableCollision(visible);
	}
}

void ARPS_MasterCube::AddElement()
{
	TArray<ERPS_States> tempStatesArray;
	mapOfStates.GetKeys(tempStatesArray);

	bool tempBool = mapOfStates.FindRef(curState);

	if (!tempBool)
	{
		mapOfStates.Add(curState, true);
		UpdateElements();

		if (!IsValid(playerCont))
		{
			return;
		}
		if (II_Cubes* intfUI = Cast<II_Cubes>(playerCont))
		{
			II_Cubes::Execute_AddElementToUI(playerCont, curState);
		}
	}
}


void ARPS_MasterCube::UpdateElements()
{
	TMap<ERPS_States, bool> L_Map;
	L_Map = mapOfStates;

	TArray<ERPS_States> L_Keys;
	L_Map.GetKeys(L_Keys);

	ERPS_States L_Rock = ERPS_States::Rock;
	ERPS_States L_Paper = ERPS_States::Paper;
	ERPS_States L_Scissor = ERPS_States::Scissors;

	for (ERPS_States state : L_Keys)
	{
		ERPS_States L_CurState = state;

		if (L_CurState != ERPS_States::Neutral)
		{
			switch (L_CurState)
			{
			case ERPS_States::Rock:

				if (L_Map.FindRef(L_Paper))
				{
					RemoveElement(L_Rock, L_Paper);
					break;
				}
				else if (L_Map.FindRef(L_Scissor))
				{
					RemoveElement(L_Scissor, L_Rock);
					break;
				}
				//AddFirstItem();
				break;


			case ERPS_States::Paper:

				if (L_Map.FindRef(L_Rock))
				{
					RemoveElement(L_Rock, L_Paper);
					break;
				}
				else if (L_Map.FindRef(L_Scissor))
				{
					RemoveElement(L_Paper, L_Scissor);
					break;
				}
				//AddFirstItem();
				break;


			case ERPS_States::Scissors:

				if (L_Map.FindRef(L_Paper))
				{
					RemoveElement(L_Paper, L_Scissor);
					break;
				}
				else if (L_Map.FindRef(L_Rock))
				{
					RemoveElement(L_Scissor, L_Rock);
					break;
				}
				//AddFirstItem();
				break;
			}
		}
	}
}

void ARPS_MasterCube::AddFirstItem()
{
	II_Cubes::Execute_UpdateCounterVal(playerCont, 1);
	II_Cubes::Execute_UpdateMaxMatches(playerCont, MaxMatches);
	II_Cubes::Execute_UpdateMod(playerCont, playerXP);
}

void ARPS_MasterCube::RemoveElement(ERPS_States Remove, ERPS_States Winner)
{
	TArray<ERPS_States> tempStatesArray;
	mapOfStates.GetKeys(tempStatesArray);

	curState = Winner;

	//bool tempBool =	mapOfStates.Find(curState);
	bool tempBool = mapOfStates.FindRef(Remove);

	if (tempBool)
	{
		mapOfStates.Add(Remove, false);
		
		UpdateMatchCount();
	}
}

void ARPS_MasterCube::UpdateMatchCount()
{
	int tempCount = matchCount + 1;
	matchCount = FMath::Clamp(tempCount, 0, MaxMatches);

	if (playerCont->GetClass()->ImplementsInterface(UI_Cubes::StaticClass()))
	{
		II_Cubes::Execute_UpdateCounterVal(playerCont, matchCount);

		if (matchCount == MaxMatches)
		{
			// Win UI response //
			UpdateMaxMatch();

			SpawnResult();
			ResetGame();
		}
	}
}


void ARPS_MasterCube::UpdateMaxMatch()
{
	playerXP++;

	if (playerXP == 10)
	{
		playerXP = FMath::RandRange(1, 10);
	}

	II_Cubes::Execute_UpdateMod(playerCont, playerXP);

	MaxMatches = playerXP;

	II_Cubes::Execute_UpdateMaxMatches(playerCont, MaxMatches);
}


void ARPS_MasterCube::ResetGame()
{
	mapOfStates.Empty();
	matchCount = 0;

	II_UI::Execute_UpdateCounter(playerCont, matchCount);
}


void ARPS_MasterCube::SpawnResult()
{
	FActorSpawnParameters Params;

	FVector offset = GetActorLocation()
					+ (GetActorForwardVector() * 200) 
					+ (GetActorUpVector() * 100);

	FTransform spawnTrasf;
	spawnTrasf.SetLocation(offset);
	
	result = GetWorld()->SpawnActor<AActor>(resultClass, spawnTrasf, Params);

	if (result)
	{
		if (II_States* states = Cast<II_States>(result))
		{
			II_States::Execute_SetState(result, curState);
		}

		UStaticMeshComponent* mesh;
		mesh = result->GetComponentByClass<UStaticMeshComponent>();

		mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		mesh->SetSimulatePhysics(true);
		mesh->SetLinearDamping(0.1f);
		mesh->SetAllMassScale(200);
	}

}
