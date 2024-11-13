// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishAnimInstance.h"
#include "Actors/NPC/Fish.h"
#include "Components/StatusComponent/FishStatusComponent.h"

void UFishAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;
	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);

	AFish* Fish = Cast<AFish>(Pawn);
	StatusComponent = Fish->GetStatusComponent();
}

void UFishAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
}
