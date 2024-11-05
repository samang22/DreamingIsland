// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/CraneGame.h"

#define CRANEGAME_CONVEYORBELT_SPEED 0.2

ACraneGame::ACraneGame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACraneGame::BeginPlay()
{
	Super::BeginPlay();
	MID = StaticMeshComponent->CreateDynamicMaterialInstance(0);
}

void ACraneGame::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACraneGame::Tick(float DeltaTime)
{
	UV.Y = FMath::Wrap(UV.Y - double(DeltaTime) * CRANEGAME_CONVEYORBELT_SPEED, 0.0, 1.0);
	MID->SetVectorParameterValue(TEXT("UV_Parameter"), UV);
}

