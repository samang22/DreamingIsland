// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/Crane.h"
#include "Misc/Utils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "Actors/Items/Item.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/NPC/CraneFence.h"

#define CRANE_SPEED							3.f
#define CRANE_DELTA_SPEED					80.f
#define CRANE_SPOTLIGHT_ANGLE				10.f
#define CRANE_SPOTLIGHT_INTENSITY			2000.f
#define CRANE_DEFAULT_LOCATION				FVector(-480.000000, -140.000000, 340.000000)

#define CRANE_Y_MAX							-140.f
#define CRANE_Y_MIN							-400.f
#define CRANE_X_MAX							280.f
#define CRANE_X_MIN							-540.f
#define CRANE_Z_MAX							340.f
#define CRANE_Z_MIN							110.f

#define CRANE_SENSE_ITEM_SPHERE_RADIUS		1024.f



ACrane::ACrane(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/Magnet/Magnet.Magnet'"));
	check(Asset.Object);

	Magnet_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magnet_StaticMeshComponent"));
	Magnet_StaticMeshComponent->SetStaticMesh(Asset.Object);
	Magnet_StaticMeshComponent->SetWorldScale3D(FVector(0.1, 0.1, 0.1));

	FRotator CurrentRotation = Magnet_StaticMeshComponent->GetRelativeRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch + 180.0f, CurrentRotation.Yaw, CurrentRotation.Roll);
	Magnet_StaticMeshComponent->SetRelativeRotation(NewRotation);

	Magnet_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Magnet_StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::BlockAll);
	RootComponent = Magnet_StaticMeshComponent;

	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Assets/Item/PM_Item.PM_Item'"));
	PhysicalMaterial = PhysMaterial.Object;

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SenseLinkCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->SetInnerConeAngle(0.f);
	SpotLightComponent->SetOuterConeAngle(CRANE_SPOTLIGHT_ANGLE);
	SpotLightComponent->Intensity = CRANE_SPOTLIGHT_INTENSITY;
	CurrentRotation = SpotLightComponent->GetRelativeRotation();
	NewRotation = FRotator(CurrentRotation.Pitch + 90.f, CurrentRotation.Yaw, CurrentRotation.Roll);
	SpotLightComponent->SetRelativeRotation(NewRotation);



	SenseItemCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SenseItemCollisionComponent"));
	SenseItemCollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SenseItemCollisionComponent->SetRelativeLocation(FVector(0.0, 100.0, 400.0));
	SenseItemCollisionComponent->SetSphereRadius(CRANE_SENSE_ITEM_SPHERE_RADIUS);
	SenseItemCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
	SenseItemCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSenseItemBeginOverlap);
	SenseItemCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSenseItemEndOverlap);

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
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Magnet_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Magnet_StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Magnet);
	Magnet_StaticMeshComponent->SetEnableGravity(false);
	//Magnet_StaticMeshComponent->SetPhysMaterialOverride(PhysicalMaterial);
	//Magnet_StaticMeshComponent->SetSimulatePhysics(true);
	//SpotLightComponent->SetWorldRotation(FVector(270.f, 0.f, 0.f).Rotation());

	SenseItemCollisionComponent->SetRelativeLocation(FVector(0.0, 100.0, 400.0));
	SenseItemCollisionComponent->SetSphereRadius(CRANE_SENSE_ITEM_SPHERE_RADIUS);
	SenseItemCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
	SenseItemCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	SenseItemCollisionComponent->RegisterComponent();
	SetActorLocation(CRANE_DEFAULT_LOCATION);

	bIsMagnetic = false;
}

void ACrane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGoDefault)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = CRANE_DEFAULT_LOCATION - CurrentLocation;
		Direction.Normalize();
		CurrentLocation += Direction * CRANE_DELTA_SPEED * DeltaTime;

		if (FVector::Dist(CurrentLocation, CRANE_DEFAULT_LOCATION) < 3.f)
		{
			CurrentLocation = CRANE_DEFAULT_LOCATION;
			bIsGoDefault = false;
			CraneFence->SetMoveUp(false);
			UKismetSystemLibrary::K2_SetTimer(this, TEXT("SetMagneticOff"), 1.f, false);
		}
		SetActorLocation(CurrentLocation);
	}
	else if (bIsUpDownMove)
	{
		FVector CurrentLocation = GetActorLocation();
		if (bIsDown)
		{
			CurrentLocation.Z += -1 * CRANE_DELTA_SPEED * DeltaTime;
			if (CurrentLocation.Z < CRANE_Z_MIN)
			{
				bIsUpDownMove = false;
				CurrentLocation.Z = CRANE_Z_MIN;
				UKismetSystemLibrary::K2_SetTimer(this, TEXT("Up"), 1.f, false);
			}
		}
		else                     
		{
			CurrentLocation.Z += +1 * CRANE_DELTA_SPEED * DeltaTime;
			if (CurrentLocation.Z > CRANE_Z_MAX)
			{
				CurrentLocation.Z = CRANE_Z_MAX;
				bIsUpDownMove = false;
				UKismetSystemLibrary::K2_SetTimer(this, TEXT("GoDefault"), 1.f, false);
			}
		}
		SetActorLocation(CurrentLocation);
	}
}

void ACrane::OnSenseItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsMagnetic)
	{
		if (AItem* Item = Cast<AItem>(OtherActor))
		{
			Item->SetMagnet(this);
		}
	}
}

void ACrane::OnSenseItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AItem* Item = Cast<AItem>(OtherActor))
	{
		Item->SetMagnet(nullptr);
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

void ACrane::Down()
{
	bIsUpDownMove = true;
	bIsDown = true;
	bIsMagnetic = true;
	bIsStart = false;
}

void ACrane::Up()
{
	bIsUpDownMove = true;
	bIsDown = false;
}

void ACrane::Move(FVector vDir, float ScaleValue)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += vDir * ScaleValue * CRANE_SPEED;
	CurrentLocation.X = FMath::Clamp(CurrentLocation.X, CRANE_X_MIN, CRANE_X_MAX);
	CurrentLocation.Y = FMath::Clamp(CurrentLocation.Y, CRANE_Y_MIN, CRANE_Y_MAX);

	SetActorLocation(CurrentLocation);
	bIsStart = true;
	//CraneFence->SetMoveUp(true);
}

void ACrane::GoDefault()
{
	bIsGoDefault = true;
}

bool ACrane::GetIsStart()
{
	return bIsStart;
}

void ACrane::OpenCraneFence()
{
	CraneFence->SetMoveUp(true);
}

void ACrane::SetMagneticOff()
{
	bIsMagnetic = false;
}

