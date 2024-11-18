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
#include "Actors/Items/Item.h"
#include "Data/NPCTableRow.h"
#include "Actors/Link/Link.h"
#include "GameInstance/DreamingIsland_GIS.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"



#define TOOLSHOPKEEPER_SPOTLIGHT_INTENSITY			12000.f
#define TSK_SAFE_LENGTH								400.f
#define TSK_LINK_RESET_POSITION						FVector(0.0, 0.0, 48.0)
#define TSK_LINK_EXECUTION_POSITION					FVector(0.0, 280.0, 48.0)
#define TSK_MAD_LOCATION							FVector(0., -120., 96.)
#define TSK_DEFAULT_LOCATION						FVector(0., -270., 66.)
#define TSK_TURN_SPEED								3.f
#define TSK_SPOTLIGHT_ANGLE							10.f

#define TSK_BEAM_EFFECT_OFFSET						30.f

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

	NPCName = NPC_Name_Korean::ToolShopKeeper;


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/FXVarietyPack/Particles/P_ky_thunderStorm.P_ky_thunderStorm'"));
	BeamEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BeamEffectComponent"));
	BeamEffectComponent->SetupAttachment(RootComponent);
	if (ParticleAsset.Object)
	{
		BeamEffectComponent->SetTemplate(ParticleAsset.Object);
	}
	FRotator CurrentRotation = BeamEffectComponent->GetRelativeRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch + 270.0f, CurrentRotation.Yaw, CurrentRotation.Roll);
	BeamEffectComponent->SetRelativeRotation(NewRotation);
	BeamEffectComponent->SetRelativeLocation(GetActorForwardVector() * TSK_BEAM_EFFECT_OFFSET);
	BeamEffectComponent->SetRelativeScale3D(FVector(0.2, 0.2, 1.0));
	BeamEffectComponent->SetAutoActivate(false);
	
}

void AToolShopKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWatching && !bIsTalking && !bIsMadOrExecution)
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
	if (bIsShootBeam) return;

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

	if (COLLISION_HIDDEN_IN_GAME)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.02f);
	}

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
				if (Distance > TSK_SAFE_LENGTH
					&& !Cast<AItem>(Link->GetCatchingItem())->GetIsPurchased())
				{
					APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
					ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
					DefaultHUD->OnSetStringToConversation(GetNPCName().ToString(), ConversationComponent->GetScript(TSK_ConversationKey::Blame));
					DefaultHUD->OnShowConversationWidget();
					DefaultHUD->OnDelayHideConversationWidget(1.f);
					UKismetSystemLibrary::K2_SetTimer(this, TEXT("SetLinkResetPosition"), 1.f, false);
					UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnLinkCaughtEnd"), 1.f, false);

					OnLinkCaught.Broadcast(GetActorLocation(), GetActorForwardVector());
					bIsWatching = false;

				}
			}
			else
			{
				if (Link->GetIsThief())
				{
					APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
					ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(PlayerController->GetHUD());
					DefaultHUD->OnSetStringToConversation(GetNPCName().ToString(), ConversationComponent->GetScript(TSK_ConversationKey::Mad));
					DefaultHUD->OnShowConversationWidget();
					DefaultHUD->OnDelayHideConversationWidget(1.f);
					UKismetSystemLibrary::K2_SetTimer(this, TEXT("SetLinkExecutionPosition"), 0.5f, false);
					UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnMadEnd"), 1.f, false);

					OnMad.Broadcast(GetActorLocation(), GetActorForwardVector());
					bIsMadOrExecution = true;
					bIsWatching = false;
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

void AToolShopKeeper::SetLinkExecutionPosition()
{
	if (TSK_Link)
	{
		TSK_Link->SetActorLocation(TSK_LINK_EXECUTION_POSITION);
	}
}

void AToolShopKeeper::CallOnLinkCaughtEnd()
{
	OnLinkCaughtEnd.Broadcast();
	bIsWatching = true;
}

void AToolShopKeeper::CallOnExecutionEnd()
{
	bIsMadOrExecution = false;
}

void AToolShopKeeper::CallOnMadEnd()
{
	OnMadEnd.Broadcast();
	SetActorLocation(TSK_MAD_LOCATION);
	//FVector MyVector = FVector(TSK_MAD_LOCATION - TSK_LINK_EXECUTION_POSITION);
	//MyVector.Z = 0.f;
	//MyVector.Normalize();

	FRotator MyRotator= FRotator(0.0, 105.9, 0.0);

	SetActorRelativeRotation(MyRotator);
	SkeletalMeshComponent->GetAnimInstance()->Montage_Play(NPCData->BeamStMontage);

	SetIsShootBeam(true);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("EndShootBeam"), 5.f, false);

}

void AToolShopKeeper::EndShootBeam()
{
	SetIsShootBeam(false);

	UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();
	Subsystem->SaveLinkData();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Field"));
}

void AToolShopKeeper::ActivateEffect()
{
	BeamEffectComponent->SetActive(true);
}
