

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include <PuzzleGame/Data/RPS_States.h>
#include <PuzzleGame/Actor/Cube/RPS_Cube.h>
#include "Framework/Interfaces/I_UI.h"
#include <PuzzleGame/Framework/Interfaces/I_Cubes.h>
#include "RPS_MasterCube.generated.h"

UCLASS()
class PUZZLEGAME_API ARPS_MasterCube : public AActor, public II_Cubes
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPS_MasterCube();

	UPROPERTY(BlueprintReadWrite)
	TArray<ARPS_Cube*> allCubes;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ARPS_Cube> curCube;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<ARPS_Cube> cubeClass;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController* playerCont;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USceneComponent* _Root;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBillboardComponent* _Billboard;



	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	ERPS_States curState;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<ERPS_States, bool> mapOfStates;




	void UpdateElements();

	void AddFirstItem();

	void RemoveElement(ERPS_States Remove, ERPS_States Winner);

	void UpdateMatchCount();

	void AddElement();

	void ResetGame();

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Rules")
	int32 playerXP;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Rules")
	int32 matchCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Rules")
	int32 MaxMatches;

	UPROPERTY(BlueprintReadWrite, Category = "Result")
	AActor* result;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Result")
	TSubclassOf<AActor> resultClass;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnCubes();
	
	void PressedButton_Implementation(ERPS_States state) override;

	void ToggleVisibility_Implementation(bool visible) override;

	void UpdateMaxMatch();

	void SpawnResult();

//	UFUNCTION(BlueprintImplementableEvent)
//	void CheckElements();

	
	
};
