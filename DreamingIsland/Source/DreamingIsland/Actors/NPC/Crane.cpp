// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Crane.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"

ACrane::ACrane(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/Magnet/Magnet.Magnet'"));
	check(Asset.Object);
	RootComponent = SkeletalMeshComponent;

	Magnet_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magnet_StaticMeshComponent"));
	Magnet_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Magnet_StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Magnet_StaticMeshComponent->SetRelativeLocation(FVector(0.0, 0.125, 0.5));
	Magnet_StaticMeshComponent->SetWorldScale3D(FVector(0.002, 0.002, 0.0015));
	Magnet_StaticMeshComponent->SetRelativeRotation(FVector(180.f, 0.f, 0.f).Rotation());
}

void ACrane::BeginPlay()
{
	Super::BeginPlay();

	FName BoneName;
	BoneName = TEXT("arm_01");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	BoneName = TEXT("arm_02");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	BoneName = TEXT("arm_03");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	BoneName = TEXT("arm_04");
	SkeletalMeshComponent->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);

	Magnet_StaticMeshComponent->SetRelativeLocation(FVector(0.0, 0.125, 0.5));
	//Magnet_StaticMeshComponent->SetWorldScale3D(FVector(0.002, 0.002, 0.0015));
	//Magnet_StaticMeshComponent->SetRelativeRotation(FVector(180.f, 0.f, 0.f).Rotation());
}

void ACrane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrane::Grab()
{
}

void ACrane::Release()
{
}

void ACrane::Down()
{
}

void ACrane::Up()
{
}

void ACrane::Move(FVector vDir)
{
}

