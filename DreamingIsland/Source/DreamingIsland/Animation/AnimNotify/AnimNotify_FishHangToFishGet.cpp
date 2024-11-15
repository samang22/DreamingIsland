// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_FishHangToFishGet.h"
#include "Actors/Link/FishingLink.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Misc/Utils.h"

UAnimNotify_FishHangToFishGet::UAnimNotify_FishHangToFishGet()
{
}

void UAnimNotify_FishHangToFishGet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AFishingLink* FishingLink = Cast<AFishingLink>(MeshComp->GetOwner());
	if (FishingLink) FishingLink->FromFishHangToFishGet();
}
