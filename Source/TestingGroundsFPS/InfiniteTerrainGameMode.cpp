// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mes Bounds Volume Pool"));
}


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}

}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * volumeToAdd)
{
	NavMeshBoundsVolumePool->AddToPool(volumeToAdd);
}
