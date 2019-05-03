// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoseNextWaypointBP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Linker.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UChoseNextWaypointBP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent())
	{
		const int index = blackboardComp->GetValueAsInt(Index.SelectedKeyName);

		if (AAIController* owner = OwnerComp.GetAIOwner())
		{
			if (ACharacter* character = Cast<ACharacter>(owner->GetPawn()))
			{
				if (UPatrolRoute* patrolRouteComponent = character->FindComponentByClass<UPatrolRoute>())
				{
					TArray<AActor*>& patrolPoints = patrolRouteComponent->PatrolPoints;

					if (patrolPoints.Num() > 0)
					{
						const int nextIndex = (index + 1) % patrolPoints.Num();
						blackboardComp->SetValueAsInt(Index.SelectedKeyName, nextIndex);
						blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPoints[index]);
					}
				}
			}
		}
	}

	return EBTNodeResult::Succeeded;
}


