// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishingLinkAnimInstance.h"
#include "Actors/Link/FishingLink.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"

UFishingLinkAnimInstance::UFishingLinkAnimInstance()
{
}

void UFishingLinkAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("ULinkAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
		return;
	}
	else if (!Pawn) { return; }

	AFishingLink* Link = Cast<AFishingLink>(Pawn);

	StatusComponent = Link->GetStatusComponent();
}

void UFishingLinkAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (StatusComponent)
	{
		bIsWait = StatusComponent->GetAnimStatus(LINK_BIT_WAIT);
	}
}

void UFishingLinkAnimInstance::PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case LINK_MONTAGE::DAMAGE:
		break;
	default:
		break;
	}

	if (tempMontage && !Montage_IsPlaying(tempMontage))
	{
		if (bIsLoop)
		{
			Montage_Play(tempMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
		}
		else
		{
			Montage_Play(tempMontage);
		}
	}
}

bool UFishingLinkAnimInstance::IsMontage(LINK_MONTAGE _InEnum)
{
	switch (_InEnum)
	{
	case LINK_MONTAGE::DAMAGE:
	default:
		return false;
		break;
	}
}

bool UFishingLinkAnimInstance::IsPlayingMontage(LINK_MONTAGE _InEnum)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case LINK_MONTAGE::DAMAGE:
		break;
	default:
		return false;
		break;
	}

	return Montage_IsPlaying(tempMontage);
}
