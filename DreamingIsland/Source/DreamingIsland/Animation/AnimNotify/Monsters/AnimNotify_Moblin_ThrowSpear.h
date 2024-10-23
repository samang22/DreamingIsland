// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Moblin_ThrowSpear.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UAnimNotify_Moblin_ThrowSpear : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_Moblin_ThrowSpear();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "ProjectileTableRow"))
	FDataTableRowHandle ProjectileTableRowHandle;
};
