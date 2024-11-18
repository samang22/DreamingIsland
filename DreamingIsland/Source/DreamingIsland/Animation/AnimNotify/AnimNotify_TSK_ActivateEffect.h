// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_TSK_ActivateEffect.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UAnimNotify_TSK_ActivateEffect : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_TSK_ActivateEffect();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
