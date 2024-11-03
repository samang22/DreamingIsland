// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ConversationComponent/ConversationComponent.h"
#include "GSOConversationComponent.generated.h"

UCLASS()
class DREAMINGISLAND_API UGSOConversationComponent : public UConversationComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
