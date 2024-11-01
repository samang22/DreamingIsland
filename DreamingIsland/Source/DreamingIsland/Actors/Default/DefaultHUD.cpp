// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/DefaultHUD.h"
#include "UI/ConversationWidget.h"
#include "UI/RupeeWidget.h"
#include "UI/ChooseWidget.h"
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

	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Rupee.UI_Rupee_C'"));
	RupeeWidget = CreateWidget<URupeeWidget>(GetWorld(), WidgetClass);
	RupeeWidget->AddToViewport();

	// 
	WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_YesOrNo.UI_YesOrNo_C'"));
	ChooseWidget = CreateWidget<UChooseWidget>(GetWorld(), WidgetClass);
	ChooseWidget->AddToViewport();
}

void ADefaultHUD::OnSetStringToConversation(FString Speaker, FString String)
{
	Widget->OnSetStringToConversation(Speaker, String);
}

void ADefaultHUD::OnShowConversationWidget()
{
	Widget->OnShow();
}

void ADefaultHUD::OnShowChooseWidget()
{
	ChooseWidget->OnShow();
}

void ADefaultHUD::OnSetRupeeNum(int RupeeNum)
{
	RupeeWidget->OnSetRupeeNum(RupeeNum);
}

void ADefaultHUD::OnSetSelection(bool bSelection)
{
	ChooseWidget->OnSetChoose(bSelection);
}

bool ADefaultHUD::GetSelection()
{
	return ChooseWidget->GetIsYes();
}

bool ADefaultHUD::GetIsChooseWidgetVisible()
{
	return ChooseWidget->GetIsVisible();
}

void ADefaultHUD::OnShowRupeeWidget()
{
	RupeeWidget->OnShow();
}

void ADefaultHUD::OnHideConversationWidget()
{
	Widget->OnHidden();
}

void ADefaultHUD::OnHideChooseWidget()
{
	ChooseWidget->OnHidden();
}

void ADefaultHUD::OnHideRupeeWidget()
{
	RupeeWidget->OnHidden();
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
