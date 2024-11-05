// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "Crane.generated.h"

class USpotLightComponent;
class USphereComponent;
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SenseItemCollisionComponent;

protected:
	bool bIsGoDefault = false;
public:
	void SetIsGoDefault(bool bFlag) { bIsGoDefault = bFlag; }

protected:
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotLightComponent;

protected:
	bool bIsMagnet = true;
public:
	void SetIsMagnet(bool bFlag) { bIsMagnet = bFlag; }
	bool GetIsMagnet() const { return bIsMagnet; }
protected:
	UFUNCTION()
	virtual void OnSenseItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetSpotLightActive();
	void SetSpotLightDeActive();


public:
	void Grab();
	void Release();
	void Down();
	void Up();
	void Move(FVector vDir, float ScaleValue);

};
