// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_TSK_BeamEnd.generated.h"


class AToolShopKeeper;
UCLASS()
class DREAMINGISLAND_API UAnimNotify_TSK_BeamEnd : public UAnimNotify
{
	GENERATED_BODY()
protected:
	AToolShopKeeper* TSK = nullptr;

public:
	UAnimNotify_TSK_BeamEnd();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
