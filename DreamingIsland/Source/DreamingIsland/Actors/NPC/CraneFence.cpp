// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/CraneFence.h"

ACraneFence::ACraneFence()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Obj/Crane/CraneFence/CraneFence.CraneFence'"));
	check(Asset.Object);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(Asset.Object);
	RootComponent = StaticMeshComponent;

	SetActorScale3D(FVector(80.0, 80.0, 80.0));
}

void ACraneFence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACraneFence::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->RegisterComponent();
	SetActorScale3D(FVector(80.0, 80.0, 80.0));
}
