// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/FishingRod.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StatusComponent/FishingRodStatusComponent.h"

// Sets default values
AFishingRod::AFishingRod()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Obj/FishingRod/FishingRod.FishingRod'"));
	check(Asset.Object);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);
	RootComponent = SkeletalMeshComponent;
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->SetRelativeScale3D(FVector(45.0, 45.0, 45.0));
	StatusComponent = CreateDefaultSubobject<UFishingRodStatusComponent>(TEXT("StatusComponent"));
}

// Called when the game starts or when spawned
void AFishingRod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFishingRod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AFishingRod::GetFishingRodEndLocation() const
{
	return SkeletalMeshComponent->GetSocketLocation(Link_SocketName::FishingRodEnd);
}

