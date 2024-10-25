// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Projectile/ProjectileTableRow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/Monster.h"

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

	//StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Link_Projectile);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCanEverAffectNavigation(false);
	USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent);
	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	StaticMeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);


	static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/DT_Projectile.DT_Projectile'"));
	check(Asset.Object);
	ProjectileDataTable = Asset.Object;



}

void AProjectile::SetData(const FName& ProjectileName, FName ProfileName, ECollisionChannel eCollisionChannel)
{
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
	CollisionComponent->RegisterComponent();

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
	CollisionComponent->bHiddenInGame = false;

}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetActorLocation();
	if (!IsValid(this)) { return; }


	//FTransform NewTransform;
	//NewTransform.SetLocation(SweepResult.ImpactPoint);
	//FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(SweepResult.ImpactNormal);
	//NewTransform.SetRotation(Rotation.Quaternion());

	// @TODO : Generate Effects

	//if (ProjectileTableRow->bUseMonster)
	//{
	//	UWorld* World = GetWorld();

	//	AMonster* Monster = World->SpawnActorDeferred<AMonster>(AMonster::StaticClass(),
	//		FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//	FTransform NewTransform;
	//	Monster->SetData(ProjectileTableRow->MonsterTableRowHandle);
	//	NewTransform.SetLocation(GetActorLocation());
	//	NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
	//	Monster->FinishSpawning(NewTransform);
	//}


	Destroy();
	UGameplayStatics::ApplyDamage(OtherActor, 1.f, OtherActor->GetInstigator()->GetController(), this, nullptr);
}

void AProjectile::OnBeginBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ProjectileTableRow->bUseMonster)
	{
		if (DataTableRowHandle.RowName == ProjectileName::Hinox_Bomb)
		{
			UWorld* World = GetWorld();

			AMonster* Monster = World->SpawnActorDeferred<AMonster>(AMonster::StaticClass(),
				FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			FTransform NewTransform;
			Monster->SetData(ProjectileTableRow->MonsterTableRowHandle);
			NewTransform.SetLocation(GetActorLocation());
			NewTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
			Monster->FinishSpawning(NewTransform);
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

