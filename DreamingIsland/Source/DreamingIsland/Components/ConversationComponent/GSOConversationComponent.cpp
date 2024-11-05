// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent/GSOConversationComponent.h"
#include "Misc/Utils.h"

void UGSOConversationComponent::BeginPlay()
{
	Super::BeginPlay();
	ScriptMap.Add(GSO_ConversationKey::Greeting, TEXT("뽑기게임샵입니다."));
	ScriptMap.Add(GSO_ConversationKey::Try, TEXT("한 판당 10루피입니다."));
	ScriptMap.Add(GSO_ConversationKey::End, TEXT("끝났습니다."));
	ScriptMap.Add(GSO_ConversationKey::Rage, TEXT("... 다신 오지 마세요 ..."));
	ScriptMap.Add(GSO_ConversationKey::BuySucceeded, TEXT("재밌게 즐겨주세요"));
	ScriptMap.Add(GSO_ConversationKey::BuyFailed, TEXT("돈이 부족하네요..."));
}
void UGSOConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
