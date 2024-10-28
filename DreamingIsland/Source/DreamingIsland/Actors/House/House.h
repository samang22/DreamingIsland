// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

struct FDataTableRowHandle;
struct FHouseTableRow;

UCLASS()
class DREAMINGISLAND_API AHouse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouse(const FObjectInitializer& ObjectInitializer);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;
	FHouseTableRow* HouseData;
};
