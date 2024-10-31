// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/Hinox/BTTask_CheckCatch.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/Monster.h"
#include "Components/StatusComponent/MonsterStatusComponent.h"
#include "Components/StatusComponent/HinoxStatusComponent.h"

UBTTask_CheckCatch::UBTTask_CheckCatch()
{
	NodeName = "CheckCatch";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CheckCatch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Monster->GetStatusComponent());
	if (!HinoxStatusComponent)
	{
		return EBTNodeResult::Failed;
	}

	const bool bCatchLink = HinoxStatusComponent->GetIsCatching();
	BlackboardComponent->SetValueAsBool(TEXT("CatchLink"), bCatchLink);

	return EBTNodeResult::Failed;
}
