// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConversationComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetStringToConversation, FString, Speaker, FString, String);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMINGISLAND_API UConversationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UConversationComponent();

protected:
	TMap<FString, FString> ScriptMap;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Conversation(FString Speaker, FString Key);
	FString GetScript(FString Key);
//public:
//	UPROPERTY(BlueprintAssignable)
//	FOnSetStringToConversation OnSetStringToConversation;
};
