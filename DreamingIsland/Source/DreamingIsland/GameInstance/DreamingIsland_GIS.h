// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/LinkData.h"

#include "DreamingIsland_GIS.generated.h"

UCLASS()
class DREAMINGISLAND_API UDreamingIsland_GIS : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	FLinkData LinkData;
public:
	void SetLinkData(FLinkData _Data) { LinkData = _Data; }
	FLinkData GetLinkData() const { return LinkData; }
};
