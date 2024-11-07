// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CuccoQuestWidget.h"
#include "Misc/Utils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UCuccoQuestWidget::UCuccoQuestWidget()
	: MaxCuccoNum(CUCCO_MAX_NUM)
{
}

void UCuccoQuestWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	FText MyCurrentCuccoNumText = FText::AsNumber(CurrentCuccoNum);
	CurrentCuccoNumText->SetText(MyCurrentCuccoNumText);
	FText MyMaxCuccoNumText = FText::AsNumber(MaxCuccoNum);
	MaxCuccoNumText->SetText(MyMaxCuccoNumText);
}

void UCuccoQuestWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCuccoQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UCuccoQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCuccoQuestWidget::OnSetCuccoNum(int CuccoNum)
{
	CurrentCuccoNum = CuccoNum;
	FText MyCurrentCuccoNumText = FText::AsNumber(CurrentCuccoNum);
	CurrentCuccoNumText->SetText(MyCurrentCuccoNumText);
}
