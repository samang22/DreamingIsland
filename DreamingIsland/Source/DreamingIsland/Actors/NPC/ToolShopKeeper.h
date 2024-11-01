// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NPC/NPC.h"
#include "ToolShopKeeper.generated.h"

#define TSK_TURN_SPEED 3.f
#define TSK_SPOTLIGHT_ANGLE 10.f

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLinkCaught, FVector, TSKLocation, FVector, ForwardVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLinkCaughtEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMad, FVector, TSKLocation, FVector, ForwardVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMadEnd);

class USpotLightComponent;
UCLASS()
class DREAMINGISLAND_API AToolShopKeeper : public ANPC
{
	GENERATED_BODY()
public:
	AToolShopKeeper(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;


protected:
	bool bToLeft = false;
	FVector LeftGoalDir;
	FVector RightGoalDir;
protected:
	bool bIsWatching = false;
public:
	void SetIsWatching(const bool _bIsWatching);

protected:
	void Tick_Watching(float DeltaTime);
	void Tick_Rotation(float DeltaTime);
	void Tick_LineTrace(float DeltaTime);
protected:
	USpotLightComponent* SpotLightComponent;

protected:
	UFUNCTION()
	void SetLinkResetPosition();
	UFUNCTION()
	void SetLinkExecutionPosition();
	AActor* TSK_Link = nullptr;



public:
	UPROPERTY(BlueprintAssignable)
	FOnLinkCaught OnLinkCaught;
	UPROPERTY(BlueprintAssignable)
	FOnLinkCaughtEnd OnLinkCaughtEnd;
	UPROPERTY(BlueprintAssignable)
	FOnMad OnMad;
	UPROPERTY(BlueprintAssignable)
	FOnMadEnd OnMadEnd;


	
protected:
	UFUNCTION()
	void CallOnLinkCaughtEnd();
	UFUNCTION()
	void CallOnExecutionEnd();
	UFUNCTION()
	void CallOnMadEnd();

protected:
	bool bIsMadOrExecution = false;
	bool bIsShootBeam = false;

public:
	void SetIsShootBeam(bool bFlag) { bIsShootBeam = bFlag; }
	void EndShootBeam();
	bool GetIsShootBeam() { return bIsShootBeam; }
};
