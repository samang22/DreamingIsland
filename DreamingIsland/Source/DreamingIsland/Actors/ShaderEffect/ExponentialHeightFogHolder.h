// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExponentialHeightFogHolder.generated.h"

class AExponentialHeightFog;
UCLASS()
class DREAMINGISLAND_API AExponentialHeightFogHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExponentialHeightFogHolder();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AExponentialHeightFog> HeightFog = nullptr;
	float GoalFogDensity = 0.f;

public:
	void SetHeightFog(AExponentialHeightFog* _HeightFog) { HeightFog = _HeightFog; }
	void SetGoalFogDensity(float _FogGoalDensity) { GoalFogDensity = _FogGoalDensity; }
};
