// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Link/FishingLink.h"
#include "Components/StatusComponent/FishingLinkStatusComponent.h"
#include "Components/CapsuleComponent.h"

AFishingLink::AFishingLink(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = tempCapsuleComponent;
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->SetCapsuleHalfHeight(LINK_CAPSULE_HALF_HEIGHT);

	StatusComponent = CreateDefaultSubobject<UFishingLinkStatusComponent>(TEXT("StatusComponent"));

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	MID_Array.Reserve(static_cast<uint32>(LINK_MATERIAL::END));

}

// Called when the game starts or when spawned
void AFishingLink::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();

	FName BoneName;
	BoneName = TEXT("arm_01");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);

	SkeletalMeshComponent->BoundsScale = 10.f;

	// CreateDynamicMaterialInstance must called in BeginPlay not Constructor
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
	return nullptr;
}

void AFishingLink::PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop)
{
}

bool AFishingLink::IsMontage(LINK_MONTAGE _InEnum)
{
	return false;
}

bool AFishingLink::IsPlayingMontage(LINK_MONTAGE _InEnum)
{
	return false;
}

