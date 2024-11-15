// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/FishingLink.h"
#include "Actors/NPC/FishingLure.h"
#include "Actors/NPC/Fish.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/FishingLinkAnimInstance.h"
#include "Gameframework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AFishingLink::AFishingLink(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = tempCapsuleComponent;
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::FishingLink);
	tempCapsuleComponent->SetCapsuleHalfHeight(LINK_CAPSULE_HALF_HEIGHT);
	tempCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StatusComponent = CreateDefaultSubobject<UFishingLinkStatusComponent>(TEXT("StatusComponent"));

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	MID_Array.Reserve(static_cast<uint32>(LINK_MATERIAL::END));


	UPawnMovementComponent* MovementComponent =GetMovementComponent();
	MovementComponent->SetActive(false);
}

// Called when the game starts or when spawned
void AFishingLink::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::FishingLink);
	tempCapsuleComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	tempCapsuleComponent->SetSimulatePhysics(false);

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();

	FName BoneName;
	BoneName = TEXT("arm_01");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);

	SkeletalMeshComponent->BoundsScale = 10.f;

	// CreateDynamicMaterialInstance func must called in BeginPlay not Constructor
	for (uint8 i = 0; i < static_cast<uint8>(LINK_MATERIAL::END); ++i)
	{
		MID_Array.Push(SkeletalMeshComponent->CreateDynamicMaterialInstance(i));
	}

	for (uint8 i = 0; i < static_cast<uint8>(LINK_MATERIAL::END); ++i)
	{
		switch (static_cast<LINK_MATERIAL>(i))
		{
		case LINK_MATERIAL::FLIPPERS:
		case LINK_MATERIAL::HOOKSHOT:
		case LINK_MATERIAL::MAGICROD:
		case LINK_MATERIAL::OCARINA:
		case LINK_MATERIAL::SHIELDA:
		case LINK_MATERIAL::SHIELDB:
		case LINK_MATERIAL::SHIELDB_MIRROR:
		case LINK_MATERIAL::SWORDA:
		case LINK_MATERIAL::SWORDA_BALL:
		case LINK_MATERIAL::SWORDB:
		case LINK_MATERIAL::SWORDB_BALL:
		case LINK_MATERIAL::SHOVEL:
		{
			FName Name_Opacity = FName(TEXT("Opacity"));
			MID_Array[i]->SetScalarParameterValue(Name_Opacity, 0.f);
		}
			break;
		default:
			break;
		}
	}
}

void AFishingLink::OnConstruction(const FTransform& Transform)
{
}

// Called every frame
void AFishingLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFishingLink::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UFishingLinkStatusComponent* AFishingLink::GetStatusComponent() const
{
	return StatusComponent;
}

void AFishingLink::PlayMontage(FISHINGLINK_MONTAGE _InEnum, bool bIsLoop)
{
	UFishingLinkAnimInstance* LinkAnimInstance = Cast<UFishingLinkAnimInstance>(GetMesh()->GetAnimInstance());
	LinkAnimInstance->PlayMontage(_InEnum, bIsLoop);
}

bool AFishingLink::IsMontage(FISHINGLINK_MONTAGE  _InEnum)
{
	UFishingLinkAnimInstance* LinkAnimInstance = Cast<UFishingLinkAnimInstance>(GetMesh()->GetAnimInstance());
	return LinkAnimInstance->IsMontage(_InEnum);
}

bool AFishingLink::IsPlayingMontage(FISHINGLINK_MONTAGE  _InEnum)
{
	UFishingLinkAnimInstance* LinkAnimInstance = Cast<UFishingLinkAnimInstance>(GetMesh()->GetAnimInstance());
	return LinkAnimInstance->IsPlayingMontage(_InEnum);
}

void AFishingLink::ThrewLure()
{
	StatusComponent->SetFishingLinkStatus(FISHINGLINK_STATUS::FISHING);
}

void AFishingLink::PullLure()
{
	if (!FishingLure) return;

	FVector Direction = GetActorLocation() - FishingLure->GetActorLocation();
	Direction.Normalize();
	
	FishingLure->AddForce(Direction * FISHINGLINK_PULL_FORCE);

	float Distance = FVector::Dist(GetActorLocation(), FishingLure->GetActorLocation());
	if (Distance < LURE_BACK_TO_LINK_DISTANCE)
	{
		FishingLure->BackToLink();
		StatusComponent->SetFishingLinkStatus(FISHINGLINK_STATUS::IDLE);

		if (FishingLure->GetCurrentFish())
		{
			PlayMontage(FISHINGLINK_MONTAGE::FISH_GET);
		}
		else
		{
			PlayMontage(FISHINGLINK_MONTAGE::FISH_LOST);
		}
		OnLinkFishGet.Broadcast(GetActorLocation(), GetActorForwardVector());
		FishingLure->SetIsFollowingActorOffset(true);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("CallOnLinkFishGetEnd"), 1.5f, false);
	}

}

void AFishingLink::CallOnLinkFishGetEnd()
{
	OnLinkFishGetEnd.Broadcast();
	if (FishingLure->GetCurrentFish()) FishingLure->GetCurrentFish()->Destroy();
	FishingLure->SetIsFollowingActorOffset(false);
}

