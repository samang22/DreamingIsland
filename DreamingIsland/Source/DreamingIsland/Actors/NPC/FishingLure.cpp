// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/FishingLure.h"
#include "Misc/Utils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#define FISHINGLURE_SPEED					5.f

#define FISHINGLURE_X_MAX					260.f
#define FISHINGLURE_X_MIN					-1320.f
#define FISHINGLURE_Z_MAX					260.f
#define FISHINGLURE_Z_MIN					80.f



AFishingLure::AFishingLure()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFishingLure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFishingLure::BeginPlay()
{
	Super::BeginPlay();
}

void AFishingLure::Move(FVector vDir, float ScaleValue)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += vDir * ScaleValue * FISHINGLURE_SPEED;
	CurrentLocation.X = FMath::Clamp(CurrentLocation.X, FISHINGLURE_X_MIN, FISHINGLURE_X_MAX);
	CurrentLocation.Z = FMath::Clamp(CurrentLocation.Y, FISHINGLURE_Z_MIN, FISHINGLURE_Z_MAX);
	SetActorLocation(CurrentLocation);
}
