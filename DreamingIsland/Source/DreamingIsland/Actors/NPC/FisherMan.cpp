// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/FisherMan.h"
#include "Misc/Utils.h"
#include "Components/ConversationComponent/FMConversationComponent.h"

AFisherMan::AFisherMan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::FisherMan;
	ConversationComponent = CreateDefaultSubobject<UFMConversationComponent>(TEXT("ConversationComponent"));
}

void AFisherMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFisherMan::BeginPlay()
{
	Super::BeginPlay();
}
