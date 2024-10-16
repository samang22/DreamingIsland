// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_StartSlash.h"

#include "Animation/LinkAnimInstance.h"

void UAnimNotify_StartSlash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ULinkAnimInstance* LinkAnimInstance = Cast<ULinkAnimInstance>(MeshComp->GetAnimInstance());
	if (LinkAnimInstance)
	{
		LinkAnimInstance->SetOffSlash();
	}
}
