// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Link.generated.h"

class UStatusComponent;
UCLASS()
class DREAMINGISLAND_API ALink : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALink(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION()
	virtual void OnDie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class USoftWheelSpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

protected:
	UAnimMontage* CurrentDieMontage;

public:
	void SetSpeedWalk();
	void SetSpeedRun();

public:
	const class ULinkStatusComponent* GetStatusComponent() const;
};
