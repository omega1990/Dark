// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoseNextWaypointBP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Linker.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChoseNextWaypointBP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent())
	{	
		const int index = blackboardComp->GetValueAsInt(Index.SelectedKeyName);

		if (AAIController* owner = OwnerComp.GetAIOwner())
		{
			APatrollingGuard* character = Cast<APatrollingGuard>(owner->GetPawn());
			if (character->PatrolPoints.Num() > 0)
			{
				const int nextIndex = (index + 1) % character->PatrolPoints.Num();
				blackboardComp->SetValueAsInt(Index.SelectedKeyName, nextIndex);
				blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, character->PatrolPoints[index]);
			}
		}
	}

	return EBTNodeResult::Succeeded;
}


