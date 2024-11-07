// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_SlashEffect.h"
#include "Actors/Link/Link.h"

UAnimNotify_SlashEffect::UAnimNotify_SlashEffect()
{
}

void UAnimNotify_SlashEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ALink* Link = Cast<ALink>(MeshComp->GetOwner());
	Link->ActivateSlashEffect();
}
