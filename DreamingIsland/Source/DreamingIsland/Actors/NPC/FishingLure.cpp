// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/FishingLure.h"
#include "Misc/Utils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AdvancedFloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Link/FishingLink.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/NPC/Fish.h"
#include "Components/StatusComponent/FishStatusComponent.h"

#define FISHINGLURE_FORCE					40000.f

#define FISHINGLURE_X_MAX					260.f
#define FISHINGLURE_X_MIN					-1320.f
#define FISHINGLURE_Z_MAX					900.f
#define FISHINGLURE_Z_MIN					80.f

#define FISHINGLURE_FORCELIMIT_Z			800.f


AFishingLure::AFishingLure()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Fishing/FishingLure/FishingLure.FishingLure'"));
	check(Asset.Object);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Lure);
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	RootComponent = CollisionComponent;



	GetFishCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("GetFishCollisionComponent"));
	GetFishCollisionComponent->SetCollisionProfileName(CollisionProfileName::SenseInteractive);
	GetFishCollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;
	GetFishCollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GetFishCollisionComponent->SetRelativeScale3D(FVector(4.0, 4.0, 4.0));
	GetFishCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	GetFishCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);


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

	const FVector CurrentLocation = GetActorLocation();
	


	if (FollowingActor)
	{
		FVector DesiredLocation = FMath::Lerp(GetActorLocation(), FollowingActor->GetActorLocation(), 0.1f);
		SetActorLocation(DesiredLocation);
	}
	else
	{
		if (CurrentLocation.Z >= FISHINGLURE_FORCELIMIT_Z)
		{
			CollisionComponent->AddForce(FVector(0.0, 0.0, -1.0) * FISHINGLURE_FORCE);
		}

		FVector NewLocation = CurrentLocation;
		NewLocation.X = FMath::Clamp(NewLocation.X, FISHINGLURE_X_MIN, FISHINGLURE_X_MAX);
		NewLocation.Z = FMath::Clamp(NewLocation.Z, FISHINGLURE_Z_MIN, FISHINGLURE_Z_MAX);
		SetActorLocation(NewLocation);

		
	}

	if (CurrentFish && FISH_STATUS::CATCHED == CurrentFish->GetStatusComponent()->GetFishStatus())
	{
		CurrentFish->SetActorLocation(GetActorLocation());
	}
}

void AFishingLure::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFishingLink* Link = Cast<AFishingLink>(Character);
	if (Link) Link->SetFishingLure(this);
	SetFollowingActor(Link);
}

void AFishingLure::Move(FVector vDir, float ScaleValue)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.Z >= FISHINGLURE_FORCELIMIT_Z) return;
	CollisionComponent->AddForce(vDir * ScaleValue * FISHINGLURE_FORCE);
}

void AFishingLure::SetFollowingActor(AActor* FA)
{
	FollowingActor = FA;
	if (FollowingActor == nullptr)
	{
		CollisionComponent->AddForce(FVector::ZeroVector, NAME_None, true);
	}
}

void AFishingLure::AddForce(FVector Velocity)
{
	CollisionComponent->AddForce(Velocity);
}

void AFishingLure::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFish* Fish = Cast<AFish>(OtherActor))
	{
		CurrentFish = Fish;
		//CurrentFish->GetStatusComponent()->SetFishStatus(FISH_STATUS::);
	}
}

void AFishingLure::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AFish* Fish = Cast<AFish>(OtherActor))
	{
		CurrentFish->GetStatusComponent()->SetFishStatus(FISH_STATUS::IDLE);
		CurrentFish = nullptr;
	}
}

void AFishingLure::PullFish()
{
	if (!CurrentFish) return;

	FVector Direction = GetActorLocation() - CurrentFish->GetActorLocation();
	Direction.Normalize();

	CurrentFish->AddForce(Direction * LURE_PULL_FORCE);
	CurrentFish->GetStatusComponent()->SetFishStatus(FISH_STATUS::FIGHTING);
}

void AFishingLure::BackToLink()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFishingLink* Link = Cast<AFishingLink>(Character);
	SetFollowingActor(Link);
	if (CurrentFish)
	{
		CurrentFish->GetStatusComponent()->SetFishStatus(FISH_STATUS::CATCHED);
		//CurrentFish->SetActorEnableCollision(false);
	}

}  