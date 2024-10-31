// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "LinkController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLinkTalk, FVector, LinkLocation, FVector, LinkLeftVector, FVector, LinkForwardVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLinkTalkEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversation, FString, Key);

UCLASS()
class DREAMINGISLAND_API ALinkController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALinkController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn);

	virtual void Tick(float DeltaTime);

protected:
	void OnWalk(const FInputActionValue& InputActionValue);
	void OnWalkOff(const FInputActionValue& InputActionValue);
	void OnRun(const FInputActionValue& InputActionValue);
	void OnRunOff(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnInteract(const FInputActionValue& InputActionValue);
	void OnLay(const FInputActionValue& InputActionValue);
	void OnZoomWheel(const FInputActionValue& InputActionValue);

protected:
	UFUNCTION()
	void OnSlashAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY()
	UInputMappingContext* IMC_Default = nullptr;

	UPROPERTY(BlueprintReadWrite)
	bool bZoomWheel = true;

	UPROPERTY(BlueprintReadWrite)
	bool bRun = false;


	UPROPERTY()
	class ULinkStatusComponent* StatusComponent;
	UPROPERTY()
	class ULinkAnimInstance* AnimInstance;

protected:
	bool bIsMoveAuto = false;
	FVector MoveAutoDirection = FVector::Zero();
	void MoveAutoSequence(float DeltaTime);
public:
	void SetMoveAuto(bool bFlag, FVector Direction = FVector::Zero());

public:
	UPROPERTY(BlueprintAssignable)
	FOnLinkTalk OnLinkTalk;
	UPROPERTY(BlueprintAssignable)
	FOnLinkTalkEnd OnLinkTalkEnd;

	UPROPERTY(BlueprintAssignable)
	FOnConversation OnConversation;
};
