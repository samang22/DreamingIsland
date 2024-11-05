// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "CraneButton.generated.h"

class ACrane;
UCLASS()
class DREAMINGISLAND_API ACraneButton : public ANPC
{
	GENERATED_BODY()
	
public:	
	ACraneButton(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ACrane> Crane;
public:
	ACrane* GetCrane() { return Crane; }

};
