// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/GameShopOwner.h"
#include "Misc/Utils.h"
#include "Components/ConversationComponent/GSOConversationComponent.h"

AGameShopOwner::AGameShopOwner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::GameShopOwner;
	ConversationComponent = CreateDefaultSubobject<UGSOConversationComponent>(TEXT("ConversationComponent"));
}

void AGameShopOwner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameShopOwner::BeginPlay()
{
	Super::BeginPlay();
}
