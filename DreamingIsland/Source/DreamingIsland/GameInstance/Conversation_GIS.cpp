// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/Conversation_GIS.h"
#include "Actors/Link/Link.h"
#include "Actors/Link/LinkController.h"
#include "Actors/NPC/NPC.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Components/StatusComponent/GSOStatusComponent.h"
#include "Actors/Default/DefaultHUD.h"
#include "Actors/Items/Item.h"
#include "Actors/NPC/Crane.h"
#include "Actors/NPC/CraneButton.h"
#include "Misc/Utils.h"
void UConversation_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UConversation_GIS::Deinitialize()
{
}

void UConversation_GIS::Conversation(ALink* Link, ANPC* NPC, bool& InbIsBroadCast)
{
	if (!Link || !NPC) return;

	ULinkStatusComponent* LinkStatusComponent = Link->GetStatusComponent();
	LinkStatusComponent->SetIsConversation(true);
	ALinkController* LinkController = Cast<ALinkController>(Link->GetController());
	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(LinkController->GetHUD());

	if (NPC->GetNPCName() == NPC_Name_Korean::ToolShopKeeper)
	{
		if (Link->IsCatchingItem())
		{
			const AItem* Item = Cast<AItem>(Link->GetCatchingItem());
			FString ItemName = Item->GetItemName().ToString();
			FString Script1 = NPC->GetScript(TEXT("Buy1")); // 은
			FString ItemValue = FString::FormatAsNumber(Item->GetItemValue());
			FString Script2 = NPC->GetScript(TEXT("Buy2")); // 루피입니다!
			FString Result = ItemName + Script1 + ItemValue + Script2;

			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Result);
			DefaultHUD->OnShowConversationWidget();
			DefaultHUD->OnShowRupeeWidget();
			DefaultHUD->OnShowChooseWidget();
		}
		else if (!Link->IsCatchingItem())
		{
			FString Script = NPC->GetScript(TEXT("Greeting"));
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);
			DefaultHUD->OnShowConversationWidget();
		}
		InbIsBroadCast = true;
	}
	else if (NPC->GetNPCName() == NPC_Name_Korean::GameShopOwner)
	{
		FString Script = NPC->GetScript(TEXT("Greeting"));
		DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);
		DefaultHUD->OnShowConversationWidget();

		InbIsBroadCast = true;
	}
	else if (NPC->GetNPCName() == NPC_Name_Korean::CraneButton)
	{
		FString Script = NPC->GetScript(TEXT("Try"));
		DefaultHUD->OnSetStringToConversation(NPC_Name_Korean::GameShopOwner.ToString(), Script);
		DefaultHUD->OnShowConversationWidget();
		DefaultHUD->OnShowRupeeWidget();
		DefaultHUD->OnShowChooseWidget();
		InbIsBroadCast = false;
	}
}

void UConversation_GIS::Purchase(ALink* Link, ANPC* NPC, bool& InbIsBroadCast)
{
	ULinkStatusComponent* StatusComponent = Link->GetStatusComponent();
	ALinkController* LinkController = Cast<ALinkController>(Link->GetController());
	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(LinkController->GetHUD());

	if (NPC_Name_Korean::ToolShopKeeper == NPC->GetNPCName())
	{
		AItem* Item = Cast<AItem>(Link->GetCatchingItem());
		if (!Item) return;
		if (StatusComponent->GetRupee() >= Item->GetItemValue())
		{
			StatusComponent->AddRupee(Item->GetItemValue() * -1);
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(TSK_ConversationKey::BuySucceeded));
			DefaultHUD->OnHideChooseWidget();
			Item->SetIsPurchased(true);
		}
		else
		{
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(TSK_ConversationKey::BuyFailed));
			DefaultHUD->OnHideChooseWidget();
		}
	}
	else if (NPC_Name_Korean::GameShopOwner == NPC->GetNPCName()
		|| NPC_Name_Korean::CraneButton == NPC->GetNPCName())
	{
		if (StatusComponent->GetRupee() >= CRANEGAME_COST)
		{
			StatusComponent->AddRupee(CRANEGAME_COST * -1);
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(GSO_ConversationKey::BuySucceeded));
			DefaultHUD->OnHideChooseWidget();
			ACraneButton* CraneButton = Cast<ACraneButton>(NPC);
			Link->SetCrane(CraneButton->GetCrane());
		}
		else
		{
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(GSO_ConversationKey::BuyFailed));
			DefaultHUD->OnHideChooseWidget();
		}
	}
}
