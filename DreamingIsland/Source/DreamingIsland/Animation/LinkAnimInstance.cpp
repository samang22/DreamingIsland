// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LinkAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Link.h"
#include "Components/LinkStatusComponent.h"


void ULinkAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("UBaisicCharacterAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
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

	isWait = StatusComponent->GetIsWait();
	isWalk = StatusComponent->GetIsWalk();
	isRun = StatusComponent->GetIsRun();
	isSlash = StatusComponent->GetIsSlash();
	isSlashHold = StatusComponent->GetIsSlashHold();
	isDeath = StatusComponent->GetIsDeath();


}

