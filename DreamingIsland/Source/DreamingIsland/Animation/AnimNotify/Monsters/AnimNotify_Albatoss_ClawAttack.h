// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Albatoss_ClawAttack.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UAnimNotify_Albatoss_ClawAttack : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_Albatoss_ClawAttack();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "ProjectileTableRow"))
	FDataTableRowHandle ProjectileTableRowHandle;
};
