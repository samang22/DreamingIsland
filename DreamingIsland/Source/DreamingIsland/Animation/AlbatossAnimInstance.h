// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MonsterAnimInstance.h"
#include "AlbatossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UAlbatossAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()

public:
	UAlbatossAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsRush = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsWait = true;
};
