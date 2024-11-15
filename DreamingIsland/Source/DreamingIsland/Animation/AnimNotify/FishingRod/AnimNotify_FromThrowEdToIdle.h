// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FromThrowEdToIdle.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UAnimNotify_FromThrowEdToIdle : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_FromThrowEdToIdle();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
