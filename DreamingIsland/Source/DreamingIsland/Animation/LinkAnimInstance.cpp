// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LinkAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Link.h"
#include "Components/LinkStatusComponent.h"


ULinkAnimInstance::ULinkAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MtgSlash(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Link/Animation/MTG_Link_SlashAttack.MTG_Link_SlashAttack'"));
	if (MtgSlash.Object)
	{
		AttackMontage = MtgSlash.Object;
	}
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

	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	bIsWait = StatusComponent->GetAnimStatus(LINK_BIT_WAIT);
	bIsWalk = StatusComponent->GetAnimStatus(LINK_BIT_WALK);
	bIsRun = StatusComponent->GetAnimStatus(LINK_BIT_RUN);
	//bIsSlash = StatusComponent->GetAnimStatus(LINK_BIT_SLASH);
	//bIsSlashHold = StatusComponent->GetAnimStatus(LINK_BIT_SLASHHOLD);
	bIsDeath = StatusComponent->GetAnimStatus(LINK_BIT_DEATH);
}

void ULinkAnimInstance::PlaySlashMontage()
{
	if (bCanSlash && AttackMontage && !Montage_IsPlaying(nullptr))
	{
		Montage_Play(AttackMontage);
	}



	//if (bCanSlash)
	//{
	//	Montage_Play(AttackMontage);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlaySlashMontage is failed"));
	//}
}

void ULinkAnimInstance::StopSlashMontage()
{
}

