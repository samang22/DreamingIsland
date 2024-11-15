// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FishingLinkAnimInstance.h"
#include "Actors/Link/FishingLink.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"

UFishingLinkAnimInstance::UFishingLinkAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgThrowLure(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_ThrowLure.MTG_Link_ThrowLure'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgFishLost(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_FishLost.MTG_Link_FishLost'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgFishGet(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_Item_Get.MTG_Link_Item_Get'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgFishHang(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_FishingLink_FishHang.MTG_FishingLink_FishHang'"));
	if (MtgThrowLure.Object) { ThrowLureMontage = MtgThrowLure.Object; }
	if (MtgFishLost.Object) { FishLostMontage = MtgFishLost.Object; }
	if (MtgFishGet.Object) { FishGetMontage = MtgFishGet.Object; }
	if (MtgFishHang.Object) { FishHangMontage = MtgFishHang.Object; }
	
}

void UFishingLinkAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("UFishingLinkAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
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
		bIsWait = StatusComponent->GetAnimStatus(FISHINGLINK_BIT_IDLE);
		bIsCastingIdle = StatusComponent->GetAnimStatus(FISHINGLINK_BIT_FISHING);
		bIsCastingReel = StatusComponent->GetAnimStatus(FISHINGLINK_BIT_PULLING);
	}
}

void UFishingLinkAnimInstance::PlayMontage(FISHINGLINK_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case FISHINGLINK_MONTAGE::THROW_LURE:
		tempMontage = ThrowLureMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_LOST:
		tempMontage = FishLostMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_GET:
		tempMontage = FishGetMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_HANG:
		tempMontage = FishHangMontage;
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

bool UFishingLinkAnimInstance::IsMontage(FISHINGLINK_MONTAGE _InEnum)
{
	switch (_InEnum)
	{
	case FISHINGLINK_MONTAGE::THROW_LURE:
		return ThrowLureMontage ? true : false;
	case FISHINGLINK_MONTAGE::FISH_LOST:
		return FishLostMontage ? true : false;
	case FISHINGLINK_MONTAGE::FISH_GET:
		return FishGetMontage ? true : false;
	case FISHINGLINK_MONTAGE::FISH_HANG:
		return FishHangMontage ? true : false;
	default:
		return false;
		break;
	}
}

bool UFishingLinkAnimInstance::IsPlayingMontage(FISHINGLINK_MONTAGE _InEnum)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case FISHINGLINK_MONTAGE::THROW_LURE:
		tempMontage = ThrowLureMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_LOST:
		tempMontage = FishLostMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_GET:
		tempMontage = FishGetMontage;
		break;
	case FISHINGLINK_MONTAGE::FISH_HANG:
		tempMontage = FishHangMontage;
	break;
	default:
		return false;
		break;
	}

	return Montage_IsPlaying(tempMontage);
}
