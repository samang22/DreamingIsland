// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent/TSKConversationComponent.h"

void UTSKConversationComponent::BeginPlay()
{
	Super::BeginPlay();
	ScriptMap.Add(TEXT("Greeting"), TEXT("도구 상점에 어서오세요!"));
	ScriptMap.Add(TEXT("Blame"), TEXT("손님! 물건은 돈 주고 가져가세요!!!"));
	ScriptMap.Add(TEXT("Bye"), TEXT("감사합니다! 또 오세요!"));
	ScriptMap.Add(TEXT("Buy1"), TEXT("은 "));
	ScriptMap.Add(TEXT("Buy2"), TEXT("루피입니다!"));
}

void UTSKConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
