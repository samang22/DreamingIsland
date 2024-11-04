// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "Crane.generated.h"

UCLASS()
class DREAMINGISLAND_API ACrane : public ANPC
{
	GENERATED_BODY()
	
public:
	ACrane(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Magnet_StaticMeshComponent;

public:
	void Grab();
	void Release();
	void Down();
	void Up();
	void Move(FVector vDir);

};
