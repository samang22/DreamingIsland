// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ConversationComponent/ConversationComponent.h"
#include "CKConversationComponent.generated.h"

UENUM()
enum EQuestStatus : int
{
	NOT_ACCEPTED = 0,
	ACCEPTED,
	SUCCEEDED,
	GREETING,
	END,
};
UCLASS()
class DREAMINGISLAND_API UCKConversationComponent : public UConversationComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	int QuestStatus = 0;
public:
	void SetQuestStatus(int _QuestStatus) { QuestStatus = _QuestStatus; }
	int GetQuestStatus() { return QuestStatus; }

protected:
	int CuccoCount = 0;
public:
	void AddCuccoCount(int _Count) { CuccoCount += _Count; }
	int GetCuccoCount() { return CuccoCount; }
};
