// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/LinkData.h"

#include "DreamingIsland_GIS.generated.h"

class ALink;
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
	void SaveLinkData();
	void LoadLinkData(ALink* Link) const;
protected:
	FVector LinkFieldLocation = FVector::Zero();
public:
	void SetLinkFieldLocation(FVector _Location) { LinkFieldLocation = _Location; }
	FVector GetLinkFieldLocation() const { return LinkFieldLocation; }

protected:
	int CuccoCount = 0;
public:
	void SetCuccoCount(int _iCount) { CuccoCount = _iCount; }
	int GetCuccoCount() const { return CuccoCount; }
};
