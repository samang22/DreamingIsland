// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TSKAnimInstance.h"
#include "Actors/NPC/NPC.h"
#include "Components/StatusComponent/NPCStatusComponent.h"

void UTSKAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;
	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);

	ANPC* NPC = Cast<ANPC>(Pawn);
	StatusComponent = NPC->GetStatusComponent();
}

void UTSKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWalk = StatusComponent->GetAnimStatus(NPC_BIT_WALK);
		bIsWait = StatusComponent->GetAnimStatus(NPC_BIT_WAIT);
		bIsTalk = StatusComponent->GetAnimStatus(NPC_BIT_TALK);
	}
}
