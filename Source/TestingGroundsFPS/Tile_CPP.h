// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.h"

#include "Tile_CPP.generated.h"

UCLASS()
class TESTINGGROUNDSFPS_API ATile_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile_CPP();

	UFUNCTION(BlueprintCallable, Category = "")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, float MinScale = 1.0f, float MaxScale = 1.0f, int MinSpawn = 1, int MaxSpawn = 1, float radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool * InPool);

private:

	bool FindEmptyLocation(FVector& OutLocation, float radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float rotation, float scale);
	bool CanSpawnAtLocation(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();
	
	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
