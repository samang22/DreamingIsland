// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "WeaponChildActorComponent.generated.h"

/**
 * 
 */
UCLASS()
class DREAMINGISLAND_API UWeaponChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()
public:
	UWeaponChildActorComponent();
	void SetData(FDataTableRowHandle InDataTableRowHandle);

};
