// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Water/Water.h"
#define WAVE_SPEED			0.3
#define WAVE_VERTICAL_SPEED 0.1
AWater::AWater()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BeachMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Map/Field/Merged/Beach/SM_Beach.SM_Beach'"));
	if (BeachMesh.Object)
	{
		StaticMeshComponent->SetStaticMesh(BeachMesh.Object);
	}
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = StaticMeshComponent;
}
void AWater::BeginPlay()
{
	Super::BeginPlay();
	MID = StaticMeshComponent->CreateDynamicMaterialInstance(0);
}

void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}