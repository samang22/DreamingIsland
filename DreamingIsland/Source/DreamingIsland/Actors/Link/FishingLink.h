// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/Utils.h"
#include "FishingLink.generated.h"

class UFishingLinkStatusComponent;
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

protected:
	UAnimMontage* SlashMontage = nullptr;
	UAnimMontage* ItemCarryMontage = nullptr;
	UAnimMontage* ItemGetMontage = nullptr;

public:
	void PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(LINK_MONTAGE _InEnum);
	bool IsPlayingMontage(LINK_MONTAGE _InEnum);

protected:
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MID_Array;
};
