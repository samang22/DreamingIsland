// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Link.generated.h"


enum class LINK_MONTAGE : uint8
{
	SLASH = 0,
	ITEM_CARRY,
	ITEM_GET,
	DEAD,
	DAMAGE,
	THROW,
	GUARD,
	END,
};

class USphereComponent;
class ULinkStatusComponent;
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
	UPROPERTY(EditAnywhere, Category = "Projectile")
	FDataTableRowHandle ProjectileTableRowHandle;

public:
	const FDataTableRowHandle GetProjectileTableRowHandle() const { return ProjectileTableRowHandle; }

public:
	void SetSpeedWalk();
	void SetSpeedRun();

public:
	const class ULinkStatusComponent* GetStatusComponent() const;
	
protected:
	bool bIsCatched = false;
	AActor* CatchingLinkActor = nullptr;

public:
	void SetIsCatched(bool _bIsCatched) { bIsCatched = _bIsCatched; }
	bool GetIsCatched() const { return bIsCatched; }
	void StopMovement();
	void ResumeMovement();
	void SetCatchingLinkActor(AActor* _CatchingLinkActor) { CatchingLinkActor = _CatchingLinkActor; }
	void StopCatchingLink() { CatchingLinkActor = nullptr; }

protected:
	void LinkCatchedSequence(float DeltaTime);

public:
	FVector GetSocketLocation(FName SocketName);


protected:
	AActor* OverlappedNPC = nullptr;
	AActor* OverlappedItem = nullptr;
	AActor* CatchingItem = nullptr;

public:
	bool IsOverlappedNPC();
	bool IsOverlappedItem();
	void CatchItem();
	void LayItem();
	bool IsCatchingItem();

protected:
	UAnimMontage* SlashMontage = nullptr;
	UAnimMontage* ItemCarryMontage = nullptr;
	UAnimMontage* ItemGetMontage = nullptr;

public:
	void PlayMontage(LINK_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(LINK_MONTAGE _InEnum);
	bool IsPlayingMontage(LINK_MONTAGE _InEnum);
};
