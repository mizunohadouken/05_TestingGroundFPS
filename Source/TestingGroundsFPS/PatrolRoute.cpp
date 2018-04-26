// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolRoute.h"


TArray<AActor*> UPatrolRoute::GetPatrolWaypoints() const
{
	return PatrolWaypoints;
}