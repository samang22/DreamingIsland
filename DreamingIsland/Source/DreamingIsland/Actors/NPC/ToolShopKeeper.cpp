// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/ToolShopKeeper.h"
#include "Misc/Utils.h"
#include "Components/SpotLightComponent.h"

AToolShopKeeper::AToolShopKeeper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetInnerConeAngle(TSK_SPOTLIGHT_ANGLE);
	SpotLightComponent->SetOuterConeAngle(TSK_SPOTLIGHT_ANGLE);
}

void AToolShopKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWatching)
	{
		Tick_Watching(DeltaTime);
	}
}

void AToolShopKeeper::BeginPlay()
{
	Super::BeginPlay();

	const FVector TSK_ForwardVector = GetActorForwardVector();
	const FVector TSK_RightVector = GetActorRightVector();
	LeftGoalDir = TSK_ForwardVector + (-1 * TSK_RightVector);
	LeftGoalDir.Normalize();
	RightGoalDir = TSK_ForwardVector + TSK_RightVector;
	RightGoalDir.Normalize();

	//

	SpotLightComponent->SetInnerConeAngle(TSK_SPOTLIGHT_ANGLE);
	SpotLightComponent->SetOuterConeAngle(TSK_SPOTLIGHT_ANGLE);
}

void AToolShopKeeper::SetIsWatching(const bool _bIsWatching)
{
	bIsWatching = _bIsWatching;
	SpotLightComponent->SetActive(bIsWatching);
}

void AToolShopKeeper::Tick_Watching(float DeltaTime)
{
	const FVector TSK_ForwardVector = GetActorForwardVector();
	const float DeltaSpeed = DeltaTime * TSK_TURN_SPEED;

	FVector NewForward;
	if (bToLeft)
	{
		NewForward = FMath::Lerp(TSK_ForwardVector, LeftGoalDir, DeltaSpeed);
		if (IsNearlyEqualVector_My(NewForward, LeftGoalDir))
		{
			bToLeft = !bToLeft;
		}
	}
	else
	{
		NewForward = FMath::Lerp(TSK_ForwardVector, RightGoalDir, DeltaSpeed);
		if (IsNearlyEqualVector_My(NewForward, RightGoalDir))
		{
			bToLeft = !bToLeft;
		}
	}
	SetActorRotation(NewForward.Rotation().Quaternion());
}
