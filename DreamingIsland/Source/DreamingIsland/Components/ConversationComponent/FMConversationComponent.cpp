// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent/FMConversationComponent.h"
#include "Misc/Utils.h"

void UFMConversationComponent::BeginPlay()
{
	Super::BeginPlay();
	ScriptMap.Add(FM_ConversationKey::Greeting, TEXT("... 반갑네"));
	ScriptMap.Add(FM_ConversationKey::Try, TEXT("... 낚시 한 번 해볼텐가?"));
	ScriptMap.Add(FM_ConversationKey::Accept, TEXT("천천히 즐기시게 ..."));
	ScriptMap.Add(FM_ConversationKey::Bad, TEXT("그래, 조용히 가주게..."));
}

void UFMConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
