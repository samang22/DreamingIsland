// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/FishingLure.h"
#include "Misc/Utils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Link/FishingLink.h"
#include "Kismet/GameplayStatics.h"

#define FISHINGLURE_SPEED					30000.f

#define FISHINGLURE_X_MAX					260.f
#define FISHINGLURE_X_MIN					-1320.f
#define FISHINGLURE_Z_MAX					800.f
#define FISHINGLURE_Z_MIN					80.f



AFishingLure::AFishingLure()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Fishing/FishingLure/FishingLure.FishingLure'"));
	check(Asset.Object);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Lure);
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	RootComponent = CollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetStaticMesh(Asset.Object);
	StaticMeshComponent->SetRelativeScale3D(FVector(90., 90., 90.));
	FRotator CurrentRotator = StaticMeshComponent->GetRelativeRotation();
	CurrentRotator.Pitch += 180.f;
	StaticMeshComponent->SetRelativeRotation(CurrentRotator);
	StaticMeshComponent->SetRelativeLocation(FVector(0.0, 0.0, 24.0));

	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Blueprint/NPC/FishingLure/PM_FishingLure.PM_FishingLure'"));
	PhysicalMaterial = PhysMaterial.Object;

	CollisionComponent->SetPhysMaterialOverride(PhysicalMaterial);
	CollisionComponent->SetEnableGravity(false);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetLinearDamping(0.8f);

}

void AFishingLure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowingActor)
	{
		SetActorLocation(FollowingActor->GetActorLocation());
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.X = FMath::Clamp(CurrentLocation.X, FISHINGLURE_X_MIN, FISHINGLURE_X_MAX);
		CurrentLocation.Z = FMath::Clamp(CurrentLocation.Z, FISHINGLURE_Z_MIN, FISHINGLURE_Z_MAX);
		SetActorLocation(CurrentLocation);
	}
}

void AFishingLure::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFishingLink* Link = Cast<AFishingLink>(Character);
	Link->SetFishingLure(this);
	SetFollowingActor(Link);
}

void AFishingLure::Move(FVector vDir, float ScaleValue)
{
	CollisionComponent->AddForce(vDir * ScaleValue * FISHINGLURE_SPEED);
}

void AFishingLure::SetFollowingActor(AActor* FA)
{
	FollowingActor = FA;
	if (FollowingActor == nullptr)
	{
		CollisionComponent->AddForce(FVector::ZeroVector, NAME_None, true);
	}
}
