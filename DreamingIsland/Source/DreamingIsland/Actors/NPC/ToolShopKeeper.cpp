// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/ToolShopKeeper.h"
#include "Misc/Utils.h"
#include "Components/SpotLightComponent.h"
#include "Components/ConversationComponent/ConversationComponent.h"
#include "Components/ConversationComponent/TSKConversationComponent.h"
#include "Actors/Link/Link.h"
#include "Actors/Link/LinkController.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Default/DefaultHUD.h"
#include "GameFramework/PlayerController.h"
#include "Actors/House/HouseCamera.h"



#define TOOLSHOPKEEPER_SPOTLIGHT_INTENSITY			12000.f
#define TSK_SAFE_LENGTH								400.f
#define TSK_LINK_RESET_POSITION						FVector(0.f, 0.f, 50.f)
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

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AActor* CameraActor = PlayerController ? PlayerController->GetViewTarget() : nullptr;
	AHouseCamera* HouseCamera = Cast<AHouseCamera>(CameraActor);
	if (HouseCamera)
	{
		// To bind delegate to HouseCamera
		HouseCamera->SetTSKDelgateBind(this);
	}

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
			TSK_Link = Link;
			if (Link->IsCatchingItem())
			{
				float Distance = FVector::Dist(Link->GetActorLocation(), GetActorLocation());
				if (Distance > TSK_SAFE_LENGTH)
				{
					APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
					ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
					DefaultHUD->OnSetStringToConversation(GetNPCName().ToString(), ConversationComponent->GetScript(TEXT("Blame")));
					DefaultHUD->OnShowConversationWidget();
					DefaultHUD->OnDelayHideConversationWidget(1.f);
					UKismetSystemLibrary::K2_SetTimer(this, TEXT("SetLinkResetPosition"), 1.f, false);

					OnLinkCaught.Broadcast(GetActorLocation(), GetActorForwardVector());
					bIsWatching = false;

					UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnLinkCaughtEnd"), 1.f, false);
				}
			}
		}
	}
}

void AToolShopKeeper::SetLinkResetPosition()
{
	if (TSK_Link)
	{
		TSK_Link->SetActorLocation(TSK_LINK_RESET_POSITION);
	}
}

void AToolShopKeeper::CallOnLinkCaughtEnd()
{
	OnLinkCaughtEnd.Broadcast();
	bIsWatching = true;
}
