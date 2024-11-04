// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Crane.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"

ACrane::ACrane(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/Crane/Crane_arm01__MI_Crane_01.Crane_arm01__MI_Crane_01'"));
	check(Asset.Object);

	Arm01_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm01_StaticMeshComponent"));
	Arm02_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm02_StaticMeshComponent"));
	Arm03_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm03_StaticMeshComponent"));
	Arm04_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm04_StaticMeshComponent"));

	Arm01_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Arm02_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Arm03_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Arm04_StaticMeshComponent->SetStaticMesh(Asset.Object);

	Arm01_StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Arm02_StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Arm03_StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Arm04_StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Arm01_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm02_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm03_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm04_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
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

	Arm01_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm02_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm03_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));
	Arm04_StaticMeshComponent->SetWorldScale3D(FVector(80.0, 80.0, 80.0));

	//(Pitch = 90.000000, Yaw = 0.000000, Roll = 0.000000)
	//(Pitch = 90.000000, Yaw = 90.000000, Roll = 0.000000)

	FQuat RotationZ = FQuat(FVector::UpVector, FMath::DegreesToRadians(90.0f));
	FQuat RotationY = FQuat(FVector::RightVector, FMath::DegreesToRadians(270.0f));
	FQuat RotationX;

	Arm01_StaticMeshComponent->SetRelativeRotation(FVector(0.0, 0.0, 90.0).Rotation());

	FQuat CombinedRotation1 = RotationZ * RotationY;
	Arm02_StaticMeshComponent->SetRelativeRotation(CombinedRotation1);

	RotationX = FQuat(FVector::ForwardVector, FMath::DegreesToRadians(90.0f));
	FQuat CombinedRotation2 = RotationZ * RotationY * RotationX;
	Arm03_StaticMeshComponent->SetRelativeRotation(CombinedRotation2);

	RotationX = FQuat(FVector::ForwardVector, FMath::DegreesToRadians(180.0f));
	FQuat CombinedRotation3 = RotationZ * RotationY * RotationX;
	Arm04_StaticMeshComponent->SetRelativeRotation(CombinedRotation3);
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

