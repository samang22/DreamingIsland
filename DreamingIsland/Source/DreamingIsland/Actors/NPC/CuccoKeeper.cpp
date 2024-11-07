// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NPC/CuccoKeeper.h"
#include "Misc/Utils.h"
#include "Components/ConversationComponent/CKConversationComponent.h"
#include "GameInstance/DreamingIsland_GIS.h"

ACuccoKeeper::ACuccoKeeper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NPCName = NPC_Name_Korean::CuccoKeeper;
	ConversationComponent = CreateDefaultSubobject<UCKConversationComponent>(TEXT("ConversationComponent"));
}

void ACuccoKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsCuccoReturned)
	{
		UDreamingIsland_GIS* Subsystem = GetGameInstance()->GetSubsystem<UDreamingIsland_GIS>();
		const int count = Subsystem->GetCuccoCount();
		if (CUCCO_MAX_NUM <= count)
		{
			bIsCuccoReturned = true;
			UCKConversationComponent* CKConversationComponent = Cast<UCKConversationComponent>(this->GetConversationComponent());
			CKConversationComponent->SetQuestStatus(EQuestStatus::SUCCEEDED);
		}
	}
}

void ACuccoKeeper::BeginPlay()
{
	Super::BeginPlay();
}
