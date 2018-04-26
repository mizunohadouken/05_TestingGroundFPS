// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PatrolRoute.h"
#include "TestingGroundsFPS/TP_ThirdPerson/PatrollingGuard.h"

#include "Classes/AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get waypoints array
	APawn* CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = CurrentPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto Waypoints = PatrolRoute->GetPatrolWaypoints();
	if (Waypoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor missing patrol points"));
		return EBTNodeResult::Failed;
	}

//	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(CurrentPawn);
//	auto Waypoints = PatrollingGuard->PatrolWaypoints;

	// Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoints[Index]);

	// Cycle index
	int32 NextIndex = (Index + 1) % Waypoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	return EBTNodeResult::Succeeded;

//	return EBTNodeResult::Type();
}
