// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/GameShopOwner.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Animation/NPCAnimInstance.h"
AGameShopOwner::AGameShopOwner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::GameShopOwner;
}

void AGameShopOwner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameShopOwner::BeginPlay()
{
	Super::BeginPlay();
}
