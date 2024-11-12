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
}

// Called when the game starts or when spawned
void AFishingLink::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* tempCapsuleComponent = GetCapsuleComponent();
	tempCapsuleComponent->SetCollisionProfileName(CollisionProfileName::Link);
	tempCapsuleComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;

	GetMesh()->BoundsScale = 10.f;
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

