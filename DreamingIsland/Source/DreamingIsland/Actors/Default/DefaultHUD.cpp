// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/DefaultHUD.h"
#include "UI/ConversationWidget.h"
#include "UI/ChooseWidget.h"
#include "UI/RupeeWidget.h"
#include "UI/ArrowWidget.h"
#include "UI/BombWidget.h"
#include "UI/CuccoQuestWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


ADefaultHUD::ADefaultHUD()
{
}

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_ConversationWidget.UI_ConversationWidget_C'"));
	Widget = CreateWidget<UConversationWidget>(GetWorld(), WidgetClass);
	Widget->AddToViewport();

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_YesOrNo.UI_YesOrNo_C'"));
	ChooseWidget = CreateWidget<UChooseWidget>(GetWorld(), WidgetClass);
	ChooseWidget->AddToViewport();

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Rupee.UI_Rupee_C'"));
	RupeeWidget = CreateWidget<URupeeWidget>(GetWorld(), WidgetClass);
	RupeeWidget->AddToViewport();

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Arrow.UI_Arrow_C'"));
	ArrowWidget = CreateWidget<UArrowWidget>(GetWorld(), WidgetClass);
	ArrowWidget->AddToViewport();

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Bomb.UI_Bomb_C'"));
	BombWidget = CreateWidget<UBombWidget>(GetWorld(), WidgetClass);
	BombWidget->AddToViewport();

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_CuccoQuest.UI_CuccoQuest_C'"));
	CuccoQuestWidget = CreateWidget<UCuccoQuestWidget>(GetWorld(), WidgetClass);
	CuccoQuestWidget->AddToViewport();
}

void ADefaultHUD::OnSetStringToConversation(FString Speaker, FString String)
{
	if (Widget)	Widget->OnSetStringToConversation(Speaker, String);
}

void ADefaultHUD::OnShowConversationWidget()
{
	if (Widget)	Widget->OnShow();
}

void ADefaultHUD::OnShowChooseWidget()
{
	if (ChooseWidget)	ChooseWidget->OnShow();
}

void ADefaultHUD::OnSetRupeeNum(int RupeeNum)
{
	if (RupeeWidget)	RupeeWidget->OnSetRupeeNum(RupeeNum);
}

void ADefaultHUD::OnSetArrowNum(int ArrowNum)
{
	if (ArrowWidget) ArrowWidget->OnSetArrowNum(ArrowNum);
}

void ADefaultHUD::OnSetBombNum(int BombNum)
{
	if (BombWidget)	BombWidget->OnSetBombNum(BombNum);
}

void ADefaultHUD::OnSetCuccoNum(int CuccoNum)
{
	if (CuccoQuestWidget) CuccoQuestWidget->OnSetCuccoNum(CuccoNum);
}

void ADefaultHUD::OnSetSelection(bool bSelection)
{
	if (ChooseWidget)	ChooseWidget->OnSetChoose(bSelection);
}

bool ADefaultHUD::GetSelection()
{
	return ChooseWidget ? ChooseWidget->GetIsYes() : false;
}

bool ADefaultHUD::GetIsChooseWidgetVisible()
{
	return ChooseWidget ? ChooseWidget->GetIsVisible() : false;
}

void ADefaultHUD::OnShowRupeeWidget()
{
	if (RupeeWidget)	RupeeWidget->OnShow();
}

void ADefaultHUD::OnShowArrowWidget()
{
	if (ArrowWidget)	ArrowWidget->OnShow();
}

void ADefaultHUD::OnShowBombWidget()
{
	if (BombWidget)	BombWidget->OnShow();
}

void ADefaultHUD::OnShowCuccoQuestWidget()
{
	if (CuccoQuestWidget)	CuccoQuestWidget->OnShow();
}

void ADefaultHUD::OnHideConversationWidget()
{
	if (Widget)	Widget->OnHidden();
}

void ADefaultHUD::OnHideChooseWidget()
{
	if (ChooseWidget)	ChooseWidget->OnHidden();
}

void ADefaultHUD::OnHideRupeeWidget()
{
	if (RupeeWidget)	RupeeWidget->OnHidden();
}

void ADefaultHUD::OnHideArrowWidget()
{
	if (ArrowWidget)	ArrowWidget->OnHidden();
}

void ADefaultHUD::OnHideBombWidget()
{
	if (BombWidget)	BombWidget->OnHidden();
}

void ADefaultHUD::OnHideCuccoQuestWidget()
{
	if (CuccoQuestWidget)	CuccoQuestWidget->OnHidden();
}

void ADefaultHUD::OnDelayHideConversationWidget(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHideConversationWidget"), Seconds, false);
}

void ADefaultHUD::OnDelayHideChooseWidget(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHideChooseWidget"), Seconds, false);
}

void ADefaultHUD::OnDelayHideRupeeWidget(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHideRupeeWidget"), Seconds, false);
}

void ADefaultHUD::OnDelayHideArrowWidget(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHideArrowWidget"), Seconds, false);
}

void ADefaultHUD::OnDelayHideBombWidget(float Seconds)
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHideHideWidget"), Seconds, false);
}

void ADefaultHUD::OnDelayHideCuccoQuestWidget(float Seconds)
{
}
