// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AlbatossAnimInstance.h"
#include "AlbatossAnimInstance.h"

void UAlbatossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAlbatossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// @TODO : Pawn으로부터 정보를 받아 애니메이션 세팅하기

	bIsDead = false;
	bIsDamage = false;
	bIsAttack = false;
	bIsRush = false;
	bIsWait = true;
}
