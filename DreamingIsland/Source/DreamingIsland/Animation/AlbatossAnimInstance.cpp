// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AlbatossAnimInstance.h"
#include "AlbatossAnimInstance.h"

UAlbatossAnimInstance::UAlbatossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgAttack(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Monsters/Albatoss/Animation/MTG_Albatoss_AttackClaw.MTG_Albatoss_AttackClaw'"));
	check(MtgAttack.Object);
	AttackMontage = MtgAttack.Object;

}

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

void UAlbatossAnimInstance::PlayClawAttack()
{
	if (AttackMontage && !Montage_IsPlaying(nullptr))
	{
		Montage_Play(AttackMontage);
	}
}
