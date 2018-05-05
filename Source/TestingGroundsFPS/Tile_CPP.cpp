// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile_CPP.h"

//#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"


// Sets default values
ATile_CPP::ATile_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MinSpawnExtent = FVector(0, -2000, 0);
	MaxSpawnExtent = FVector(4000, 2000, 0);

}

void ATile_CPP::PlaceActors(TSubclassOf<AActor> ToSpawn, float MinScale, float MaxScale, int MinSpawn, int MaxSpawn, float radius)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(SpawnPoint, radius * RandomScale);
		if (found)
		{
			float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandomScale);
		}
	}
}

bool ATile_CPP::FindEmptyLocation(FVector& OutLocation, float radius)
{
	FBox Bounds(MinSpawnExtent, MaxSpawnExtent);
	
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

void ATile_CPP::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float rotation, float scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, rotation, 0));
	Spawned->SetActorScale3D(FVector(scale));
}

// Called when the game starts or when spawned
void ATile_CPP::BeginPlay()
{
	Super::BeginPlay();

	CanSpawnAtLocation(GetActorLocation(), 300);
	CanSpawnAtLocation(GetActorLocation() + FVector(0, 0, 1000), 300);
	
}

void ATile_CPP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->ReturnToPool(NavMeshBoundsVolume);
}

// Called every frame
void ATile_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile_CPP::SetPool(UActorPool * InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile_CPP::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

bool ATile_CPP::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);


	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

//	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
//	DrawDebugCapsule(GetWorld(), GlobalLocation,0, Radius,FQuat::Identity, ResultColor, true, 100);

	return !HasHit;
}

