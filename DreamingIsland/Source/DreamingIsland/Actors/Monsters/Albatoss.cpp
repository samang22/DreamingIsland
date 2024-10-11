// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Albatoss.h"
#include "Albatoss.h"

AAlbatoss::AAlbatoss(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AAlbatoss::PostLoad()
{
	Super::PostLoad();
}

void AAlbatoss::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AAlbatoss::BeginPlay()
{
	Super::BeginPlay();
}

void AAlbatoss::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

float AAlbatoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AAlbatoss::OnDie()
{
	Super::OnDie();
}

void AAlbatoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
