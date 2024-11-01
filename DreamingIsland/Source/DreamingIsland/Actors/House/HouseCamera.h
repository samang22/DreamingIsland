// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseCamera.generated.h"

class AToolShopKeeper;
UCLASS()
class DREAMINGISLAND_API AHouseCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouseCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

protected:
	UPROPERTY(EditAnywhere)
	FVector DefaultLocation = FVector::Zero();
	UPROPERTY(EditAnywhere)
	FRotator DefaultRotator = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	FVector DesiredLocation = FVector::Zero();
	UPROPERTY(EditAnywhere)
	FRotator DesiredRotator = FRotator::ZeroRotator;

public:
	UFUNCTION()
	void OnLinkTalk(FVector LinkLocation, FVector LinkLeftVector, FVector LinkForwardVector);
	UFUNCTION()
	void OnLinkTalkEnd();
	UFUNCTION()
	void OnLinkCaught(FVector TSKLocation, FVector ForwardVector);
	UFUNCTION()
	void OnLinkCaughtEnd();
	UFUNCTION()
	void OnLinkItemGet(FVector LinkLocation, FVector ForwardVector);
	UFUNCTION()
	void OnLinkItemGetEnded();

protected:
	AToolShopKeeper* ToolShopKeeper = nullptr;
public:
	void SetTSKDelgateBind(AToolShopKeeper* _Keeper);
};
