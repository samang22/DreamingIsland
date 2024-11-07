// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "Cucco.generated.h"



UCLASS()
class DREAMINGISLAND_API ACucco : public ANPC
{
	GENERATED_BODY()

public:
	ACucco(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


protected:
	bool bIsCatched = false;
	AActor* CatchingCuccoActor = nullptr;

public:
	void SetIsCatched(bool _bIsCatched) { bIsCatched = _bIsCatched; }
	bool GetIsCatched() const { return bIsCatched; }
	void StopMovement();
	void ResumeMovement();
	void SetCatchingCuccoActor(AActor* _CatchingCuccoActor) { CatchingCuccoActor = _CatchingCuccoActor; }
	void ClearCatchingCuccoActor() { CatchingCuccoActor = nullptr; }

protected:
	void CuccoCatchedSequence(float DeltaTime);

protected:
	bool bIsRun = false;
	FVector RunDirection = FVector::Zero();
public:
	void SetCuccoRunWithDirection(FVector _Direction);
	void SetCuccoRunEnd();
	void Thrown();
	void Landed();
};
