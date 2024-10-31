// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/ToolShopKeeper.h"
#include "Misc/Utils.h"
#include "Components/SpotLightComponent.h"
#include "Components/ConversationComponent/ConversationComponent.h"
#include "Components/ConversationComponent/TSKConversationComponent.h"
#include "Actors/Link/Link.h"

#define TOOLSHOPKEEPER_SPOTLIGHT_INTENSITY 8000.f

AToolShopKeeper::AToolShopKeeper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetInnerConeAngle(0.f);
	SpotLightComponent->SetOuterConeAngle(TSK_SPOTLIGHT_ANGLE);

	// Default Value is 5000.f
	SpotLightComponent->Intensity = TOOLSHOPKEEPER_SPOTLIGHT_INTENSITY;

	ConversationComponent = CreateDefaultSubobject<UTSKConversationComponent>(TEXT("ConversationComponent"));

	Name = TEXT("도구 상점 주인");
}

void AToolShopKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWatching && !bIsTalking)
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
	SpotLightComponent->Intensity = TOOLSHOPKEEPER_SPOTLIGHT_INTENSITY;
}

void AToolShopKeeper::SetIsWatching(const bool _bIsWatching)
{
	bIsWatching = _bIsWatching;
	SpotLightComponent->SetActive(bIsWatching);
}

void AToolShopKeeper::Tick_Watching(float DeltaTime)
{
	Tick_Rotation(DeltaTime);
	Tick_LineTrace(DeltaTime);
}

void AToolShopKeeper::Tick_Rotation(float DeltaTime)
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

void AToolShopKeeper::Tick_LineTrace(float DeltaTime)
{
	const FVector Start = GetActorLocation();
	const FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + (ForwardVector * 10000.0f); 

	TArray<FHitResult> HitResults;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, TRACE_CHANNEL_LINKCHANNEL, CollisionParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.02f);

	static int iCount = 0;
	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (ALink* Link = Cast<ALink>(HitActor))
		{
			if (Link->IsCatchingItem())
			{
				ConversationComponent->Conversation(Name.ToString(), TEXT("Blame"));
			}
		}
	}
}
