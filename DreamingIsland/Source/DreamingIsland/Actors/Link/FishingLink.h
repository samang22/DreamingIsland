// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/Utils.h"
#include "FishingLink.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLinkFishGet, FVector, LinkLocation, FVector, LinkForwardVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLinkFishGetEnd);

class AFishingLure;
class UFishingLinkStatusComponent;
class AFishingRod;
class ULineBatchComponent;

UCLASS()
class DREAMINGISLAND_API AFishingLink : public ACharacter
{
	GENERATED_BODY()

public:
	AFishingLink(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere)
	UFishingLinkStatusComponent* StatusComponent;

public:
	UFishingLinkStatusComponent* GetStatusComponent() const;

public:
	void PlayMontage(FISHINGLINK_MONTAGE  _InEnum, bool bIsLoop = false);
	bool IsMontage(FISHINGLINK_MONTAGE  _InEnum);
	bool IsPlayingMontage(FISHINGLINK_MONTAGE  _InEnum);

protected:
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MID_Array;

protected:
	TObjectPtr<AFishingLure> FishingLure;
public:
	AFishingLure* GetFishingLure() const { return FishingLure; }
	void SetFishingLure(AFishingLure* _Lure) { FishingLure = _Lure; }
	void ThrewLure();
	void PullLure();

public:
	UFUNCTION()
	void CallOnLinkFishGetEnd();

public:
	UPROPERTY(BlueprintAssignable)
	FOnLinkFishGet OnLinkFishGet;
	UPROPERTY(BlueprintAssignable)
	FOnLinkFishGetEnd OnLinkFishGetEnd;

protected:
	TObjectPtr<AFishingRod> FishingRod = nullptr;
	void KeepFishingRodInHand(float _DeltaTime);

public:
	void FromFishHangToFishGet();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULineBatchComponent> LineBatchComponent;
};
