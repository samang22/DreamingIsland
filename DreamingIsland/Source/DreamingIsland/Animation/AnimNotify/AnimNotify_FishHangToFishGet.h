// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FishHangToFishGet.generated.h"

UCLASS()
class DREAMINGISLAND_API UAnimNotify_FishHangToFishGet : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_FishHangToFishGet();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
