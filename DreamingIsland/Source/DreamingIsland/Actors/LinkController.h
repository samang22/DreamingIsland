// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "LinkController.generated.h"
/**
 * 
 */



UCLASS()
class DREAMINGISLAND_API ALinkController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALinkController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	/**
	 * Overridable native function for when this controller is asked to possess a pawn.
	 * @param InPawn The Pawn to be possessed
	 */
	virtual void OnPossess(APawn* InPawn);

protected:
	void OnWalk(const FInputActionValue& InputActionValue);
	void OnWalkOff(const FInputActionValue& InputActionValue);
	void OnRun(const FInputActionValue& InputActionValue);
	void OnRunOff(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnInteract(const FInputActionValue& InputActionValue);
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



};
