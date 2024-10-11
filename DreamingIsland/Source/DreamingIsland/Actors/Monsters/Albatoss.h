// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Monster.h"
#include "Albatoss.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API AAlbatoss : public AMonster
{
	GENERATED_BODY()


protected:
	AAlbatoss(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void OnDie();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
