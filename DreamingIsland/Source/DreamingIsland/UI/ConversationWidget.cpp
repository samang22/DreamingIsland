// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ConversationWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UConversationWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPawn();
	SetVisibility(ESlateVisibility::Hidden);
}

void UConversationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UConversationWidget::OnHiddenUI()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UConversationWidget::OnSetStringToConversation(FString _Speaker, FString String)
{
	FText tempText = FText::FromString(String);
	TextBlock->SetText(tempText);

	tempText = FText::FromString(_Speaker);
	Speaker->SetText(tempText);
}
