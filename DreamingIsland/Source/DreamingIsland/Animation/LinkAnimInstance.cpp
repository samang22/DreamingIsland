// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LinkAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Link/Link.h"
#include "Components/StatusComponent/LinkStatusComponent.h"


ULinkAnimInstance::ULinkAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgSlash(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_Slash.MTG_Link_Slash'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgItemCarry(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_Item_Carry.MTG_Link_Item_Carry'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgItemGet(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_Item_Get.MTG_Link_Item_Get'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgThrow(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_Throw.MTG_Link_Throw'"));
	if (MtgSlash.Object) { SlashMontage = MtgSlash.Object; }
	if (MtgItemCarry.Object) { ItemCarryMontage = MtgItemCarry.Object; }
	if (MtgItemGet.Object) { ItemGetMontage = MtgItemGet.Object; }
	if (MtgThrow.Object) { ThrowMontage = MtgThrow.Object; }
}

void ULinkAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("ULinkAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
		return;
	}
	else if (!Pawn) { return; }

	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);

	ALink* Link = Cast<ALink>(Pawn);

	StatusComponent = Link->GetStatusComponent();

}

void ULinkAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	//Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	bIsWait = StatusComponent->GetAnimStatus(LINK_BIT_WAIT);
	bIsWalk = StatusComponent->GetAnimStatus(LINK_BIT_WALK);
	bIsRun = StatusComponent->GetAnimStatus(LINK_BIT_RUN);
	bIsCarry = StatusComponent->GetAnimStatus(LINK_BIT_CARRY);
	bIsBataBata = StatusComponent->GetAnimStatus(LINK_BIT_BATABATA);
}

void ULinkAnimInstance::PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case LINK_MONTAGE::SLASH:
		tempMontage = SlashMontage;
		break;
	case LINK_MONTAGE::ITEM_CARRY:
		tempMontage = ItemCarryMontage;
		break;
	case LINK_MONTAGE::ITEM_GET:
		tempMontage = ItemGetMontage;
		break;
	case LINK_MONTAGE::THROW:
		tempMontage = ThrowMontage;
		break;
	case LINK_MONTAGE::DEAD:
		break;
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

bool ULinkAnimInstance::IsMontage(LINK_MONTAGE _InEnum)
{
	switch (_InEnum)
	{
	case LINK_MONTAGE::SLASH:
		return SlashMontage ? true : false;
		break;
	case LINK_MONTAGE::ITEM_CARRY:
		return ItemCarryMontage ? true : false;
		break;
	case LINK_MONTAGE::ITEM_GET:
		return ItemGetMontage ? true : false;
		break;
	case LINK_MONTAGE::THROW:
		return ThrowMontage ? true : false;
		break;
	case LINK_MONTAGE::DEAD:
	case LINK_MONTAGE::DAMAGE:
	case LINK_MONTAGE::GUARD:
	default:
		check(false);
		return false;
		break;
	}
}

bool ULinkAnimInstance::IsPlayingMontage(LINK_MONTAGE _InEnum)
{
	UAnimMontage* tempMontage = nullptr;
	switch (_InEnum)
	{
	case LINK_MONTAGE::SLASH:
		tempMontage = SlashMontage;
		break;
	case LINK_MONTAGE::ITEM_CARRY:
		tempMontage = ItemCarryMontage;
		break;
	case LINK_MONTAGE::ITEM_GET:
		tempMontage = ItemGetMontage;
		break;
	case LINK_MONTAGE::THROW:
		tempMontage = ThrowMontage;
		break;
	case LINK_MONTAGE::END:
		tempMontage = nullptr;
		break;
	case LINK_MONTAGE::DEAD:
	case LINK_MONTAGE::DAMAGE:
	default:
		check(false);
		return false;
		break;
	}

	return Montage_IsPlaying(tempMontage);
}

//void ULinkAnimInstance::PlayAttackMontage()
//{
//	if (!Montage_IsPlaying(nullptr))
//	{
//		Montage_Play(AttackMontage);
//	}
//}
//
//void ULinkAnimInstance::PlayDieMontage()
//{
//	Montage_Play(DieMontage);
//}
//
//void ULinkAnimInstance::PlayItemCarryMontage()
//{
//	if (!Montage_IsPlaying(nullptr))
//	{
//		Montage_Play(ItemCarryMontage);
//	}
//}
//
//void ULinkAnimInstance::PlayItemGetMontage()
//{
//	if (!Montage_IsPlaying(nullptr))
//	{
//		Montage_Play(ItemGetMontage);
//	}
//}
