// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent/TSKConversationComponent.h"
#include "Misc/Utils.h"

void UTSKConversationComponent::BeginPlay()
{
	Super::BeginPlay();
	ScriptMap.Add(TSK_ConversationKey::Greeting, TEXT("도구 상점에 어서오세요!"));
	ScriptMap.Add(TSK_ConversationKey::Blame, TEXT("손님! 물건은 돈 주고 가져가세요!!!"));
	ScriptMap.Add(TSK_ConversationKey::Bye, TEXT("감사합니다! 또 오세요!"));
	ScriptMap.Add(TSK_ConversationKey::Buy1, TEXT("은 "));
	ScriptMap.Add(TSK_ConversationKey::Buy2, TEXT("루피입니다!"));
	ScriptMap.Add(TSK_ConversationKey::BuySucceeded, TEXT("감사합니다!"));
	ScriptMap.Add(TSK_ConversationKey::BuyFailed, TEXT("잔액이 부족합니다..."));
}

void UTSKConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
