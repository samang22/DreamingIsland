// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Monster.h"
#include "Components/MonsterStatusComponent.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;
	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);

	AMonster* Monster = Cast<AMonster>(Pawn);
	StatusComponent = Monster->GetStatusComponent();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	//if (MovementComponent)
	//{
	//	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
	//}

}