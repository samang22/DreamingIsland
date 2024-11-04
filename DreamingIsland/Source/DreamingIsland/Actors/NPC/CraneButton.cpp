// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/CraneButton.h"
#include "Components/SphereComponent.h"
#include "Misc/Utils.h"
#include "Animation/CraneButtonAnimInstance.h"
#include "Components/ConversationComponent/GSOConversationComponent.h"

// Sets default values
ACraneButton::ACraneButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// UGSOConversationComponent is meant to be
	ConversationComponent = CreateDefaultSubobject<UGSOConversationComponent>(TEXT("ConversationComponent"));
}

void ACraneButton::BeginPlay()
{
	Super::BeginPlay();
	NPCName = NPC_Name_Korean::CraneButton;

}


void ACraneButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


