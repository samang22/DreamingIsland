// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Data/PawnTableRow.h"
#include "Monster.generated.h"

#define AISENSECONFIG_SIGHT_SIGHTRADIUS										700.f
#define AISENSECONFIG_SIGHT_LOSESIGHTRADIUS									600.f
#define AISENSECONFIG_SIGHT_LOSESIGHTRADIUS_PERIPHERALVISIONANGLEDEGREES	120.f

#define ALBATOSS_CLAWATTACK_LENGTH 70.f
#define OCTOROK_ROCKATTACK_LENGTH 50.f


enum class MONSTER_MONTAGE : uint8
{
	ATTACK = 0,
	DEAD,
	DAMAGE,
	RUSH,
	FIND,
	KYOROKYORO,
	END,
};



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

class UAdvancedFloatingPawnMovement;
class UMonsterStatusComponent;
class APatrolPath;
class UWeaponChildActorComponent;
UCLASS()
class DREAMINGISLAND_API AMonster : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	//AMonster();
	AMonster(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UShapeComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	UAdvancedFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UMonsterStatusComponent* StatusComponent;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FPawnTableRow* MonsterData;

public:
	const FPawnTableRow* GetMonsterData() const { return MonsterData; }
protected:
	UPROPERTY()
	FString MonsterName;

public:
	void PlayMontage(MONSTER_MONTAGE _InEnum);
	bool IsMontage(MONSTER_MONTAGE _InEnum);
	bool IsPlayingMontage(MONSTER_MONTAGE _InEnum);



protected:
	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	class UAISenseConfig_Sight* AISenseConfig_Sight;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<APatrolPath> PatrolPathRef;


public:
	UMonsterStatusComponent* GetStatusComponent() { return StatusComponent; }


protected:
	void TickMovement(float DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponChildActorComponent> Weapon;

protected:
	bool bIsWeaponEquiped = false;
public:
	bool GetIsWeaponEquiped();
	void SetWeaponEquiped();
	void SetWeaponUnEquiped();
	void RenderOffWeapon();
	void RenderOnWeapon();


};
