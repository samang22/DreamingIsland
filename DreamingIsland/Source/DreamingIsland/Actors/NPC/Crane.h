// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "Crane.generated.h"

class USpotLightComponent;
class USphereComponent;
class ACraneFence;
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
	UPhysicalMaterial* PhysicalMaterial = nullptr;

protected:
	bool bIsMagnetic = true;
public:
	void SetIsMagnetic(bool bFlag) { bIsMagnetic = bFlag; }
	bool GetIsMagnetic() const { return bIsMagnetic; }
protected:
	UFUNCTION()
	virtual void OnSenseItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSenseItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void SetSpotLightActive();
	void SetSpotLightDeActive();

protected:
	bool bIsUpDownMove = false;
	bool bIsDown = false;
	bool bIsStart = false;
public:
	UFUNCTION()
	void Up();
	void Down();
	void Move(FVector vDir, float ScaleValue);
	UFUNCTION()
	void GoDefault();
	bool GetIsStart();
	UFUNCTION()
	void OpenCraneFence();
	UFUNCTION()
	void SetMagneticOff();
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ACraneFence> CraneFence;
public:
	ACraneFence* GetCraneFence() { return CraneFence; }

protected:
	TArray<TObjectPtr<AActor>> CatchingItem_Array;

};
