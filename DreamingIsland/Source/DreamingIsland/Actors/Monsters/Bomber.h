// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Monsters/Monster.h"
#include "Bomber.generated.h"

class UMaterialInterface;
class UTexture;
class UParticleSystemComponent;
class UParticleSystem;
UCLASS()
class DREAMINGISLAND_API ABomber : public AMonster
{
	GENERATED_BODY()
public:
	ABomber(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UMaterialInterface* MaterialInterface;
	UMaterialInstanceDynamic* DynamicMaterialInstance;

protected:
	UTexture* Texture_Default = nullptr;
	UTexture* Texture_Smile = nullptr;
	UTexture* Texture_1 = nullptr;
	UTexture* Texture_2 = nullptr;
	UTexture* Texture_3 = nullptr;

protected:
	float ElapsedTime = 0.f;

protected:
	void SpawnProjectileAndDestory();

protected:
	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> ExplosionEffectComponent;
	TObjectPtr<UParticleSystem> ExplosionParticleAsset;
public:
	void ActivateExplosionEffect();
};
