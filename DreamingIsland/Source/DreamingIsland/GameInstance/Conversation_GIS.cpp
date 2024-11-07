// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/Conversation_GIS.h"
#include "Misc/Utils.h"
#include "Actors/Link/Link.h"
#include "Actors/Link/LinkController.h"
#include "Actors/Default/DefaultHUD.h"
#include "Actors/Items/Item.h"
#include "Actors/NPC/NPC.h"
#include "Actors/NPC/Crane.h"
#include "Actors/NPC/CraneButton.h"
#include "Actors/NPC/CraneFence.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Components/ConversationComponent/CKConversationComponent.h"
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
			FString Script1 = NPC->GetScript(TSK_ConversationKey::Buy1); // 은
			FString ItemValue = FString::FormatAsNumber(Item->GetItemValue());
			FString Script2 = NPC->GetScript(TSK_ConversationKey::Buy2); // 루피입니다!
			FString Result = ItemName + Script1 + ItemValue + Script2;

			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Result);
			DefaultHUD->OnShowConversationWidget();
			DefaultHUD->OnShowRupeeWidget();
			DefaultHUD->OnShowChooseWidget();
		}
		else if (!Link->IsCatchingItem())
		{
			FString Script = NPC->GetScript(TSK_ConversationKey::Greeting);
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);
			DefaultHUD->OnShowConversationWidget();
		}
		InbIsBroadCast = true;
	}
	else if (NPC->GetNPCName() == NPC_Name_Korean::GameShopOwner)
	{
		FString Script = NPC->GetScript(GSO_ConversationKey::Greeting);
		DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), Script);
		DefaultHUD->OnShowConversationWidget();

		InbIsBroadCast = true;
	}
	else if (NPC->GetNPCName() == NPC_Name_Korean::CraneButton)
	{
		FString Script = NPC->GetScript(GSO_ConversationKey::Try);
		DefaultHUD->OnSetStringToConversation(NPC_Name_Korean::GameShopOwner.ToString(), Script);
		DefaultHUD->OnShowConversationWidget();
		DefaultHUD->OnShowRupeeWidget();
		DefaultHUD->OnShowChooseWidget();
		InbIsBroadCast = false;
	}
	else if (NPC_Name_Korean::CuccoKeeper == NPC->GetNPCName())
	{
		UCKConversationComponent* ConversationComponent = Cast<UCKConversationComponent>(NPC->GetConversationComponent());
		FString Script;
		switch (ConversationComponent->GetQuestStatus())
		{
		case NOT_ACCEPTED:
			Script = NPC->GetScript(CK_ConversationKey::Request);
			DefaultHUD->OnShowChooseWidget();
			break;
		case ACCEPTED:
			Script = NPC->GetScript(CK_ConversationKey::Accept);
			break;
		case SUCCEEDED:
			Script = NPC->GetScript(CK_ConversationKey::Thanks);
			ConversationComponent->SetQuestStatus(EQuestStatus::GREETING);
			break;
		case GREETING:
			Script = NPC->GetScript(CK_ConversationKey::Greeting);
			break;
		default:
			break;

		}

		DefaultHUD->OnSetStringToConversation(NPC_Name_Korean::CuccoKeeper.ToString(), Script);
		DefaultHUD->OnShowConversationWidget();
		InbIsBroadCast = true;
	}
}

void UConversation_GIS::Check(ALink* Link, ANPC* NPC, bool& InbIsEndTalk, bool bCheck)
{
	ULinkStatusComponent* StatusComponent = Link->GetStatusComponent();

	if (NPC_Name_Korean::ToolShopKeeper == NPC->GetNPCName())
	{
		if (bCheck)
		{
			bool bCheckBroadcast = false;
			Purchase(Link, NPC, bCheckBroadcast);
			StatusComponent->SetIsConversation(false);
		}
		else
		{
			InbIsEndTalk = true;
			StatusComponent->SetIsConversation(false);
		}
	}
	else if (NPC_Name_Korean::GameShopOwner == NPC->GetNPCName()
		|| NPC_Name_Korean::CraneButton == NPC->GetNPCName())
	{
		if (bCheck)
		{
			bool bCheckBroadcast = false;
			Purchase(Link, NPC, bCheckBroadcast);
			StatusComponent->SetIsConversation(false);
		}
		else
		{
			InbIsEndTalk = true;
			StatusComponent->SetIsConversation(false);

		}
	}
	// Quest from CuccoKeeper
	else if (NPC_Name_Korean::CuccoKeeper == NPC->GetNPCName())
	{
		if (bCheck)
		{
			UCKConversationComponent* ConversationComponent = Cast<UCKConversationComponent>(NPC->GetConversationComponent());
			ConversationComponent->SetQuestStatus(EQuestStatus::ACCEPTED);

			bool bCheckBroadcast = false;
			Purchase(Link, NPC, bCheckBroadcast);
			StatusComponent->SetIsConversation(false);
		}
		else
		{
			//InbIsEndTalk = true;
			//StatusComponent->SetIsConversation(false);
			ALinkController* LinkController = Cast<ALinkController>(Link->GetController());
			ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(LinkController->GetHUD());
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(CK_ConversationKey::Bad));
			DefaultHUD->OnHideChooseWidget();
		}
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
		if (StatusComponent->GetRupee() >= CRANEGAME_COST
			&& !Link->IsCrane())
		{
			StatusComponent->AddRupee(CRANEGAME_COST * -1);
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(GSO_ConversationKey::BuySucceeded));
			DefaultHUD->OnHideChooseWidget();
			ACraneButton* CraneButton = Cast<ACraneButton>(NPC);
			CraneButton->GetCrane()->GetCraneFence()->SetMoveUp(true);
			Link->SetCrane(CraneButton->GetCrane());
			DefaultHUD->OnDelayHideConversationWidget(1.f);
		}
		else
		{
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(GSO_ConversationKey::BuyFailed));
			DefaultHUD->OnHideChooseWidget();
			DefaultHUD->OnDelayHideConversationWidget(1.f);
		}
	}
	// Quest from CuccoKeeper
	else if (NPC_Name_Korean::CuccoKeeper == NPC->GetNPCName())
	{
		UCKConversationComponent* ConversationComponent = Cast<UCKConversationComponent>(NPC->GetConversationComponent());
		if (ConversationComponent->GetQuestStatus() == EQuestStatus::ACCEPTED)
		{
			DefaultHUD->OnSetStringToConversation(NPC->GetNPCName().ToString(), NPC->GetScript(CK_ConversationKey::Accept));
		}
		DefaultHUD->OnHideChooseWidget();
	}


}
