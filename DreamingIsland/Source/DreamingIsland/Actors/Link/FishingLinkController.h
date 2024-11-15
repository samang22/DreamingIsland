// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"

#include "FishingLinkController.generated.h"



UCLASS()
class DREAMINGISLAND_API AFishingLinkController : public APlayerController
{
	GENERATED_BODY()
public:
	AFishingLinkController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn);

	virtual void Tick(float DeltaTime);

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnThrow(const FInputActionValue& InputActionValue);
	void OnPull(const FInputActionValue& InputActionValue);
	void OnShake(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY()
	UInputMappingContext* IMC_Default = nullptr;

	UPROPERTY()
	class UFishingLinkStatusComponent* StatusComponent;
	UPROPERTY()
	class UFishingLinkAnimInstance* AnimInstance;


};
