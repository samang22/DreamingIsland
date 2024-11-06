// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/CuccoKeeper.h"
#include "Misc/Utils.h"
#include "Components/ConversationComponent/CKConversationComponent.h"

ACuccoKeeper::ACuccoKeeper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::CuccoKeeper;
	ConversationComponent = CreateDefaultSubobject<UCKConversationComponent>(TEXT("ConversationComponent"));
}

void ACuccoKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACuccoKeeper::BeginPlay()
{
	Super::BeginPlay();
}
