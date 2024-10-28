// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/House/Crane/CraneButton.h"

// Sets default values
ACraneButton::ACraneButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACraneButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraneButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

