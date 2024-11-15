// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Misc/Utils.h"
#include "FishingLinkAnimInstance.generated.h"

UCLASS()
class DREAMINGISLAND_API UFishingLinkAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFishingLinkAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	const class UFishingLinkStatusComponent* StatusComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCastingIdle = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCastingReel = false;

protected:
	UAnimMontage* FishLostMontage;
	UAnimMontage* ThrowLureMontage;
	UAnimMontage* FishGetMontage;

public:
	void PlayMontage(FISHINGLINK_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(FISHINGLINK_MONTAGE _InEnum);
	bool IsPlayingMontage(FISHINGLINK_MONTAGE _InEnum);
};
