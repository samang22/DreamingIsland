// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ToCraneGameTriggerBox.generated.h"

class UBoxComponent;
UCLASS()
class DREAMINGISLAND_API AToCraneGameTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AToCraneGameTriggerBox(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

protected:
	UFUNCTION()
	void OnActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> ActiveCollisionComponent;
};
