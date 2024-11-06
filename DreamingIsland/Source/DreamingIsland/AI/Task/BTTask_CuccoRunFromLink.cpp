// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_CuccoRunFromLink.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actors/NPC/Cucco.h"
#include "Misc/Utils.h"

UBTTask_CuccoRunFromLink::UBTTask_CuccoRunFromLink()
{
	NodeName = "CuccoRunFromLink";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CuccoRunFromLink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACucco* Cucco = Cast<ACucco>(AIOwner->GetPawn());
	if (!Character || !Cucco)
	{
		return EBTNodeResult::Failed;
	}

	FVector LinkLocation = Character->GetActorLocation();
	FVector CuccoLocation = Cucco->GetActorLocation();

	FVector Direction = CuccoLocation - LinkLocation;
	Direction.Normalize();

	Cucco->SetCuccoRunWithDirection(Direction);

	return EBTNodeResult::InProgress;
}

void UBTTask_CuccoRunFromLink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACucco* Cucco = Cast<ACucco>(AIOwner->GetPawn());
	if (!Character || !Cucco)
	{
		Cucco->SetCuccoRunEnd();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (FVector::Dist(Character->GetActorLocation(), Cucco->GetActorLocation()) > CUCCO_AISENSECONFIG_SIGHT_LOSESIGHTRADIUS)
	{
		Cucco->SetCuccoRunEnd();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

}
