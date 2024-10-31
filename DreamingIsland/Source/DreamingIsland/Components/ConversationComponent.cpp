// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ConversationComponent.h"

// Sets default values for this component's properties
UConversationComponent::UConversationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UConversationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UConversationComponent::Conversation(FString Speaker, FString Key)
{
	FString Value = *ScriptMap.Find(Key);
}

FString UConversationComponent::GetScript(FString Key)
{
	return *ScriptMap.Find(Key);
}
