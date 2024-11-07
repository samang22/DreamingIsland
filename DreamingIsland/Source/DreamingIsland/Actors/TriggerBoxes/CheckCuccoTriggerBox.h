// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckCuccoTriggerBox.generated.h"

UCLASS()
class DREAMINGISLAND_API ACheckCuccoTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ACheckCuccoTriggerBox(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

protected:
	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
