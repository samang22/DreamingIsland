// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Crane.h"
#include "Misc/Utils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"

#define CRANE_SPEED							3.f
#define CRANE_SPOTLIGHT_ANGLE				10.f
#define CRANE_SPOTLIGHT_INTENSITY			12000.f
#define CRANE_DEFAULT_LOCATION				FVector(-480.000000, -140.000000, 342.000000)

#define CRANE_Y_MAX							-140.f
#define CRANE_Y_MIN							-400.f
#define CRANE_X_MAX							280.f
#define CRANE_X_MIN							-540.f

ACrane::ACrane(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/Magnet/Magnet.Magnet'"));
	check(Asset.Object);

	Magnet_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magnet_StaticMeshComponent"));
	Magnet_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Magnet_StaticMeshComponent->SetRelativeLocation(FVector(0.0, 0.125, 0.5));
	Magnet_StaticMeshComponent->SetWorldScale3D(FVector(0.002, 0.002, 0.0015));
	Magnet_StaticMeshComponent->SetRelativeRotation(FVector(180.f, 0.f, 0.f).Rotation());
	Magnet_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Magnet_StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::BlockAll);
	RootComponent = Magnet_StaticMeshComponent;

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SenseLinkCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetInnerConeAngle(0.f);
	SpotLightComponent->SetOuterConeAngle(CRANE_SPOTLIGHT_ANGLE);
	SpotLightComponent->Intensity = CRANE_SPOTLIGHT_INTENSITY;
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

	SenseLinkCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionProfileName(CollisionProfileName::BlockAll);

	Magnet_StaticMeshComponent->SetRelativeLocation(FVector(0.0, 0.125, 0.5));
	Magnet_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Magnet_StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::BlockAll);
	//SpotLightComponent->SetWorldRotation(FVector(270.f, 0.f, 0.f).Rotation());


	SetActorLocation(CRANE_DEFAULT_LOCATION);
}

void ACrane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGoDefault)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = FMath::Lerp(CurrentLocation, CRANE_DEFAULT_LOCATION, 0.1f);
		SetActorLocation(CurrentLocation);
	}
}

void ACrane::SetSpotLightActive()
{
	SpotLightComponent->SetActive(true);
}

void ACrane::SetSpotLightDeActive()
{
	SpotLightComponent->SetActive(false);
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

void ACrane::Move(FVector vDir, float ScaleValue)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += vDir * ScaleValue * CRANE_SPEED;
	CurrentLocation.X = FMath::Clamp(CurrentLocation.X, CRANE_X_MIN, CRANE_X_MAX);
	CurrentLocation.Y = FMath::Clamp(CurrentLocation.Y, CRANE_Y_MIN, CRANE_Y_MAX);

	SetActorLocation(CurrentLocation);
}

