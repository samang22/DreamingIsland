// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/Utils.h"
#include "Link.generated.h"




class USphereComponent;
class ULinkStatusComponent;
class ACrane;
class UNiagaraComponent;
class USpotLightComponent;
class URectLightComponent;

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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnSenseInteractiveBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSenseInteractiveEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<class USoftWheelSpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	ULinkStatusComponent* StatusComponent;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SenseInteractCollisionComponent;

protected:
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MID_Array;

public:
	void ActiveSpringArm();
	void DeActiveSpringArm();

protected:
	FVector DesiredCameraLocation;
	FRotator DesiredCameraRotator;
	FVector DefaultCameraLocation;
	FRotator DefaultCameraRotator;
	bool bCameraZoom = false;
public:
	UFUNCTION()
	void OnLinkItemGet(FVector LinkLocation, FVector ForwardVector);
protected:
	UFUNCTION()
	void OnLinkItemGetEnd();

protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	FDataTableRowHandle ProjectileTableRowHandle;

public:
	const FDataTableRowHandle GetProjectileTableRowHandle() const { return ProjectileTableRowHandle; }

public:
	void SetSpeedWalk();
	void SetSpeedRun();

public:
	class ULinkStatusComponent* GetStatusComponent() const;

protected:
	bool bIsCatched = false;
	AActor* CatchingLinkActor = nullptr;

public:
	void SetIsCatched(bool _bIsCatched) { bIsCatched = _bIsCatched; }
	bool GetIsCatched() const { return bIsCatched; }
	void StopMovement();
	void ResumeMovement();
public:
	void SetCatchingLinkActor(AActor* _CatchingLinkActor) { CatchingLinkActor = _CatchingLinkActor; }
	void StopCatchingLink() { CatchingLinkActor = nullptr; }

protected:
	void LinkCatchedSequence(float DeltaTime);

public:
	FVector GetSocketLocation(FName SocketName);


protected:
	TObjectPtr<AActor> OverlappedNPC = nullptr;
	TObjectPtr<AActor> OverlappedItem = nullptr;
	TObjectPtr<AActor> CatchingActor = nullptr;
public:
	bool IsOverlappedNPC();
	bool IsOverlappedItem();
	void CatchItem();
	void ActorThrown();
	bool IsCatchingActor();
	AActor* GetOverlappedNPC() const { return OverlappedNPC; }
	AActor* GetCatchingActor() const { return CatchingActor; }
	void SetCatchingActor(AActor* Projectile);


	void DestoryCatchingItem();
	void SetOffAnimStatus(uint8 Bit);
	void CatchCucco();


protected:
	void SetDataFromGIS();

protected:
	UAnimMontage* SlashMontage = nullptr;
	UAnimMontage* ItemCarryMontage = nullptr;
	UAnimMontage* ItemGetMontage = nullptr;

public:
	void PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(LINK_MONTAGE _InEnum);
	bool IsPlayingMontage(LINK_MONTAGE _InEnum);

protected:
	bool bIsMoveAuto = false;
public:
	void SetMoveAuto(bool bFlag, FVector Direction = FVector::Zero());

public:
	UFUNCTION()
	void OnLinkTalk(FVector LinkLocation, FVector LinkLeftVector, FVector LinkForwardVector);
	UFUNCTION()
	void OnLinkTalkEnd();

public:
	void SetIsThief(bool bFlag);
	bool GetIsThief();

public:
	void SetCrane(ACrane* Crane);
	void ClearCrane();
	bool IsCrane();

protected:
	UPROPERTY()
	TArray<TObjectPtr<UNiagaraComponent>> SlashEffectComponent_Array;
	int SlashEffectIndex = 0;
public:
	void ActivateSlashEffect();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpotLightComponent> SpotLightComponent = nullptr;
public:
	void SetSpotLightActive(bool bFlag);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<URectLightComponent> RectLightComponent = nullptr;
public:
	void SetRectLightActive(bool bFlag);

public:
	void SetMaterialOpacity(LINK_MATERIAL eMaterial, float Opacity);


};
