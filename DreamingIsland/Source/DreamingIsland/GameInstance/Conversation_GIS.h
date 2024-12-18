// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Conversation_GIS.generated.h"

class ALink;
class ANPC;
UCLASS()
class DREAMINGISLAND_API UConversation_GIS : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void Conversation(ALink* Link, ANPC* NPC, bool& InbIsBroadCast);
	void Check(ALink* Link, ANPC* NPC, bool& InbIsTalkEnd, bool bCheck);
	void Purchase(ALink* Link, ANPC* NPC, bool& InbIsBroadCast);
};
