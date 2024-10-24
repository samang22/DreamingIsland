#include "AI/Task/BTTask_MonsterAttack.h"
#include "Animation/MonsterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
//#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
//#include "Misc/Utils.h"
#include "Actors/Monster.h"



UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	NodeName = "MonsterAttack";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());

	// Rotate to Link
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Character || !Monster)
	{
		return EBTNodeResult::Failed;
	}
	FVector Dir = Character->GetActorLocation() - Monster->GetActorLocation();
	Dir.Normalize();

	if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	{
		Monster->SetActorRotation(Dir.Rotation().Quaternion());
		Monster->PlayMontage(MONSTER_MONTAGE::ATTACK);
	}



	return EBTNodeResult::Failed;
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(AIOwner->GetPawn());
	if (Monster->IsPlayingMontage(MONSTER_MONTAGE::DAMAGE))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	if (!Monster->IsPlayingMontage(MONSTER_MONTAGE::ATTACK))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}


