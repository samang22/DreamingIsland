// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Monster.h"
#include "Moriblin.generated.h"

// this class derived from AMonster to make Guard 

#define MORIBLIN_SHIELD_DEGREE 120.f

UCLASS()
class DREAMINGISLAND_API AMoriblin : public AMonster
{
	GENERATED_BODY()

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
