// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Pawn.h"
#include "Misc/Utils.h"
#include "Fish.generated.h"

class USphereComponent;
class APatrolPath;
class UAdvancedFloatingPawnMovement;
class UFishStatusComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FFishTableRow;

UCLASS()
class DREAMINGISLAND_API AFish : public APawn
{
	GENERATED_BODY()
public:
	AFish(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<APatrolPath> PatrolPathRef;
	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UAdvancedFloatingPawnMovement> MovementComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFishStatusComponent> StatusComponent;

	
protected:
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	TObjectPtr<USphereComponent> CollisionComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

public:
	FName GetFishName() const { return DataTableRowHandle.RowName; }

public:
	TObjectPtr<UFishStatusComponent> GetStatusComponent() { return StatusComponent; }
	//TObjectPtr<UAdvancedFloatingPawnMovement> GetMovementComponent();

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FFishTableRow* FishData;

protected:
	TObjectPtr<UPhysicalMaterial> PhysicalMaterial = nullptr;

public:
	void SetCollisionProfileName(FName CollisionProfile);

public:
	void PlayMontage(FISH_MONTAGE _InEnum, bool bIsLoop = false);
	bool IsMontage(FISH_MONTAGE _InEnum);
	bool IsPlayingMontage(FISH_MONTAGE _InEnum);

public:
	void AddForce(FVector Direction);

protected:
	FVector DesiredDirection = FVector::ZeroVector;
public:
	void SetDesiredDirection(FVector _Dir) { DesiredDirection = _Dir; }
	void SetPhysicsLinearVelocity(FVector _Velocity);
};
