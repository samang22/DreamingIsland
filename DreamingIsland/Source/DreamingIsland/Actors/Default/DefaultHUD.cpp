// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/DefaultHUD.h"
#include "UI/ConversationWidget.h"
#include "Blueprint/UserWidget.h"


ADefaultHUD::ADefaultHUD()
{
}

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_ConversationWidget.UI_ConversationWidget_C'"));
	Widget = CreateWidget<UConversationWidget>(GetWorld(), WidgetClass);
	Widget->AddToViewport();
}

void ADefaultHUD::OnSetStringToConversation(FString Speaker, FString String)
{
	Widget->OnSetStringToConversation(Speaker, String);
}
