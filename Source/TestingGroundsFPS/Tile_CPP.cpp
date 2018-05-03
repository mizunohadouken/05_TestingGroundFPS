// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile_CPP.h"


// Sets default values
ATile_CPP::ATile_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile_CPP::PlaceActors()
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	for (size_t i = 0; i < 20; i++)
	{
		FVector RandSpawnPoint = FMath::RandPointInBox(Bounds);
//		UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *RandSpawnPoint.ToCompactString());
		UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *RandSpawnPoint.ToString());
	}
}

// Called when the game starts or when spawned
void ATile_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

