// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/Monsters/Monster.h"
#include "Actors/Monsters/Bomber.h"
#include "Actors/Monsters/Hinox.h"
#include "Actors/Link/Link.h"
#include "Actors/Items/Item.h"
#include "Actors/NPC/Cucco.h"

#include "Components/StatusComponent/HinoxStatusComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 100.0;
	ProjectileMovementComponent->MaxSpeed = 100.0;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0;
	InitialLifeSpan = 5.f;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCanEverAffectNavigation(false);
	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	StaticMeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);


	/*static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/DT_Projectile.DT_Projectile'"));
	check(Asset.Object);
	ProjectileDataTable = Asset.Object;*/



}

void AProjectile::SetData(const FName& ProjectileName, FName ProfileName)
{
	if (!ProjectileDataTable)
	{
		ProjectileDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Data/DT_Projectile.DT_Projectile'"));
		check(ProjectileDataTable);
	}
	if (!ProjectileDataTable->GetRowMap().Find(ProjectileName)) { ensure(false); return; }
	DataTableRowHandle.DataTable = ProjectileDataTable;
	DataTableRowHandle.RowName = ProjectileName;
	ProjectileTableRow = DataTableRowHandle.GetRow<FProjectileTableRow>(DataTableRowHandle.RowName.ToString());

	StaticMeshComponent->MoveIgnoreActors.Empty();
	StaticMeshComponent->MoveIgnoreActors.Add(GetOwner());

	if (ProjectileTableRow->StaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(ProjectileTableRow->StaticMesh);
		StaticMeshComponent->SetWorldTransform(ProjectileTableRow->Transform);
	}





	CollisionComponent->SetCollisionProfileName(ProfileName);

	ProjectileMovementComponent->MaxSpeed = ProjectileTableRow->MaxSpeed;
	ProjectileMovementComponent->InitialSpeed = ProjectileTableRow->InitialSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileTableRow->GravityScale;

	if (USphereComponent* SphereCom = Cast<USphereComponent>(CollisionComponent))
	{
		SphereCom->SetSphereRadius(ProjectileTableRow->CollisionSphereRadius);
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->bHiddenInGame = COLLISION_HIDDEN_IN_GAME;

}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetActorLocation();
	if (!IsValid(this)) { return; }

	// @TODO : Generate Effects

	if (DataTableRowHandle.RowName == ProjectileName::Hinox_Catch)
	{
		AActor* tempOwner = GetOwner();
		AHinox* Hinox = Cast<AHinox>(tempOwner);
		if (Hinox)
		{
			ALink* Link = Cast<ALink>(OtherActor);
			if (Link)
			{
				Link->StopMovement();
				Link->SetCatchingLinkActor(Hinox);
				Link->SetIsCatched(true);
				UHinoxStatusComponent* HinoxStatusComponent = Cast<UHinoxStatusComponent>(Hinox->GetStatusComponent());
				HinoxStatusComponent->SetIsCatching(true);
			}
		}
	}
	else
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileTableRow->Damage, OtherActor->GetInstigator()->GetController(), this, nullptr);
	}

	Destroy();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ProjectileTableRow->bUseMonster)
	{
		if (DataTableRowHandle.RowName == ProjectileName::Hinox_Bomb)
		{
			UWorld* World = GetWorld();

			ABomber* Monster = World->SpawnActorDeferred<ABomber>(ABomber::StaticClass(),
				FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			FTransform NewTransform;
			Monster->SetData(ProjectileTableRow->MonsterTableRowHandle);
			NewTransform.SetLocation(GetActorLocation());
			NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
			Monster->FinishSpawning(NewTransform);
		}
	}
	if (DataTableRowHandle.RowName == ProjectileName::Hinox_Link)
	{
		AHinox* Hinox = Cast<AHinox>(Owner);
		if (Hinox)
		{
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			ALink* Link = Cast<ALink>(Character);
			if (Link)
			{
				Link->ResumeMovement();
				Link->SetCatchingLinkActor(nullptr);
				Link->SetIsCatched(false);
			}
		}
	}
	else if (DataTableRowHandle.RowName == ProjectileName::Link_Throw)
	{
		if (CatchingActor)
		{
			if (ACucco* Cucco = Cast<ACucco>(CatchingActor))
			{
				Cucco->ResumeMovement();
				Cucco->ClearCatchingCuccoActor();
				Cucco->SetIsCatched(false);
				Cucco->Landed();
			}
			else if (AItem* Item = Cast<AItem>(CatchingActor))
			{
				if (Item)
				{
					Item->SetItemCatched(false);
					Item->SetCatchingItemActor(nullptr);
				}
			}
		}
	}
	Destroy();
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionComponent->GetCollisionObjectType();

}

FVector AProjectile::GetVelocity()
{
	FVector Direction = ProjectileMovementComponent->Velocity;
	return Direction;
}

