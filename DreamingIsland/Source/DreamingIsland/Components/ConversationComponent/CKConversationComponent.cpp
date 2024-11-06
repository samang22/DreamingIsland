// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent/CKConversationComponent.h"
#include "Misc/Utils.h"

void UCKConversationComponent::BeginPlay()
{
	Super::BeginPlay();
	ScriptMap.Add(CK_ConversationKey::Greeting, TEXT("만나서 반갑네"));
	ScriptMap.Add(CK_ConversationKey::Request, TEXT("닭들이 죄다 도망갔는데 나를 좀 도와주지 않겠는가?"));
	ScriptMap.Add(CK_ConversationKey::Thanks, TEXT("정말 고맙네. 자네 아니었으면 정말 큰일이었을거야."));
	ScriptMap.Add(CK_ConversationKey::Accept, TEXT("고맙네, 기대하고 있겠네"));
	ScriptMap.Add(CK_ConversationKey::Bad, TEXT("그거 아쉽구만..."));
	ScriptMap.Add(CK_ConversationKey::NotYet, TEXT("아직 닭들이 부족하네"));
}

void UCKConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
