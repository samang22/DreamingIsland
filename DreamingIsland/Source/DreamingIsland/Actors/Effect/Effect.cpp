// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Effect/Effect.h"

AEffect::AEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEffect::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

