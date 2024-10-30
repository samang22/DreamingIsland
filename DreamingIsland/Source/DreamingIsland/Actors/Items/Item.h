// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemTableRow;
class USphereComponent;
class UCharacterMovementComponent;

UCLASS()
class DREAMINGISLAND_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer);
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FItemTableRow* ItemData;

public:
	FName GetItemName() { return DataTableRowHandle.RowName; }

protected:
	void ItemCatchedSequence(float DeltaTime);
	bool bIsItemCatched = false;
	AActor* CatchingItemActor = nullptr;
public:
	void SetItemCatched(bool _bIsItemCatched) { bIsItemCatched = _bIsItemCatched; }
	void SetCatchingItemActor(AActor* _CatchingItemActor) { CatchingItemActor = _CatchingItemActor;	}
};
