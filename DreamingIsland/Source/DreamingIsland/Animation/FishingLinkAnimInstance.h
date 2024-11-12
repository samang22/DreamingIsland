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
	bool bIsWait = true;

protected:
	UAnimMontage* PullingMontage;

public:
	void PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(LINK_MONTAGE _InEnum);
	bool IsPlayingMontage(LINK_MONTAGE _InEnum);
};
