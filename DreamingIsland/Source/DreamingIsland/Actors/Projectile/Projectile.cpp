// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileTableRow.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 100.0;
	ProjectileMovementComponent->MaxSpeed = 100.0;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0;
	InitialLifeSpan = 5.f;

	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Link_Projectile);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

}

void AProjectile::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetActorLocation();
	if (!IsValid(this)) { return; }

	// BeginPlay 시점에 Overlapped 되면 들어 옴
	if (!bFromSweep)
	{
		Destroy();
		check(false);
		return;
	}

	FTransform NewTransform;
	NewTransform.SetLocation(SweepResult.ImpactPoint);
	FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(SweepResult.ImpactNormal);
	NewTransform.SetRotation(Rotation.Quaternion());

	// @TODO : Generate Effects

	Destroy();

	UGameplayStatics::ApplyDamage(OtherActor, 1.f, GetInstigator()->GetController(), this, nullptr);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

