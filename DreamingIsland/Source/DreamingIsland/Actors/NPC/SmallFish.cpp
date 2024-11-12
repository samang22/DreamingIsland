// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/SmallFish.h"
#include "Misc/Utils.h"

ASmallFish::ASmallFish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::FisherMan;
}

void ASmallFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASmallFish::BeginPlay()
{
	Super::BeginPlay();
}
