// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Data/PawnTableRow.h"
#include "Monster.generated.h"


class UMonsterAnimInstance;

UCLASS()
class UMonsterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	TSubclassOf<UMonsterAnimInstance> AnimClass;
	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	FTransform SkeletalMeshTransform;

public:
	UMonsterDataAsset();

};

class UFloatingPawnMovement;
class UMonsterStatusComponent;

UCLASS()
class DREAMINGISLAND_API AMonster : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	//AMonster();
	AMonster(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle, FString Key);

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UFUNCTION()
	virtual void OnDie();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected: // 옵션에 따라 생성되고 Root로 지정 됩니다.
	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UMonsterStatusComponent* StatusComponent;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FPawnTableRow* MonsterData;

protected:
	UPROPERTY()
	FString MonsterName;

public:
	void PlayAttackMontage();
	void PlayDieMontage();
	void PlayDamageMontage();

protected:
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	class UAISenseConfig_Sight* AISenseConfig_Sight;

public:
	UMonsterStatusComponent* GetStatusComponent() { return StatusComponent; }

};
