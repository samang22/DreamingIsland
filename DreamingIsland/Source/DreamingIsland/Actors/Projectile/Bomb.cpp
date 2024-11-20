// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile/Bomb.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"



ABomb::ABomb()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(CollisionProfileName::BombProjectile);
	CollisionComponent->SetSphereRadius(32.f);
	RootComponent = CollisionComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Script/Engine.Material'/Game/Assets/Item/Bomb/MI_bomb.MI_bomb'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMeshObj.Object)
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshObj.Object);
	}
	StaticMeshComponent->SetWorldScale3D(FVector(90.0, 90.0, 90.0));

	//static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Script/PhysicsCore.PhysicalMaterial'/Game/Assets/Item/PM_Item.PM_Item'"));
	//PhysicalMaterial = PhysMaterial.Object;

	
}

void ABomb::BeginPlay()
{
	//if (!HasAnyFlags(RF_ClassDefaultObject))
	//{
	//	CollisionComponent->SetPhysMaterialOverride(PhysicalMaterial);
	//	CollisionComponent->SetEnableGravity(true);
	//	CollisionComponent->SetSimulatePhysics(true);
	//}
}
void ABomb::Explosion()
{
}
void ABomb::Tick(float DeltaTime)
{

}

