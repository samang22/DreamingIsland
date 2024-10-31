// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_StopSlash.h"
#include "Actors/Link/LinkController.h"
#include "GameFramework/Character.h"
#include "Animation/LinkAnimInstance.h"

void UAnimNotify_StopSlash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//ULinkAnimInstance* LinkAnimInstance = nullptr;
	//if (MeshComp)
	//{
	//	LinkAnimInstance = Cast<ULinkAnimInstance>(MeshComp->GetAnimInstance());
	//}
	//if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	//{
	//	// 애니메이션 몽타주를 멈춤
	//	Character->StopAnimMontage(LinkAnimInstance->GetAttackMontage());
	//}
}
