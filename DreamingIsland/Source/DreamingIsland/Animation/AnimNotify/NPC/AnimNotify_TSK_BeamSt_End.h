// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_TSK_BeamSt_End.generated.h"

UCLASS()
class DREAMINGISLAND_API UAnimNotify_TSK_BeamSt_End : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_TSK_BeamSt_End();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
