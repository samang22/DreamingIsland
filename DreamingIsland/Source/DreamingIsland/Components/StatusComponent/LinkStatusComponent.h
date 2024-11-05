// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent/StatusComponent.h"
#include "LinkStatusComponent.generated.h"

class ACrane;
UCLASS()
class DREAMINGISLAND_API ULinkStatusComponent : public UStatusComponent
{
	GENERATED_BODY()
	
public:
	ULinkStatusComponent();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	uint8 LinkAnimationStatus;
	//UPROPERTY()
	//uint8 LinkToolOwnStatus;
	UPROPERTY()
	uint8 LinkToolEquipStatus;

public:
	void SetOnAnimationStatus(uint8 InBit);
	void SetOffAnimationStatus(uint8 InBit);

//public:
//	void SetOnToolOwnStatus(uint8 InBit);
//	void SetOffToolOwnStatus(uint8 InBit);

public:
	void SetOnToolEquipStatus(uint8 InBit);
	void SetOffToolEquipStatus(uint8 InBit);


public:
	UFUNCTION()
	bool GetAnimStatus(uint8 InBit) const;
	//UFUNCTION()
	//bool GetToolOwnStatus(uint8 InBit) const;
	UFUNCTION()
	bool GetToolEquipStatus(uint8 InBit) const;
	UFUNCTION()
	uint8 GetEntireToolEquipStatus() const;

protected:
	bool bIsCatched = false;
public:
	void SetIsCatched(bool _bIsCatched) { bIsCatched = _bIsCatched; }
	bool GetIsCatched() const { return bIsCatched; }


protected:
	int Rupee = 0;
public:
	void SetRupee(int _Rupee);
	void AddRupee(int _Rupee);
	int GetRupee() const;

protected:
	int Bomb = 0;
public:
	void SetBomb(int _Bomb);
	void AddBomb(int _Bomb);
	int GetBomb() const;

protected:
	int Arrow = 0;
public:
	void SetArrow(int _Arrow);
	void AddArrow(int _Arrow);
	int GetArrow() const;

protected:
	bool bIsConversation = false;;
public:
	void SetIsConversation(bool _bIsConversation) { bIsConversation = _bIsConversation; }
	bool GetIsConversation() const { return bIsConversation; }

protected:
	bool bIsThief = false;
public:
	void SetIsThief(bool bFlag) { bIsThief = bFlag; }
	bool GetIsThief() { return bIsThief; }

protected:
	ACrane* Crane = nullptr;
public:
	void SetCrane(ACrane* _Crane) { Crane = _Crane; }
	void ClearCrane() { Crane = nullptr; }
	ACrane* GetCrane() const { return Crane; }
};
