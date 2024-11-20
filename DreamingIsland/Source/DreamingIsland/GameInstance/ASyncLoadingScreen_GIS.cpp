// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ASyncLoadingScreen_GIS.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer.h"
#include "Kismet/GameplayStatics.h"

void UASyncLoadingScreen_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UASyncLoadingScreen_GIS::ShowLoadingScreen(TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	UserWidget->AddToViewport();
	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreenAttributes;
		LoadingScreenAttributes.WidgetLoadingScreen = UserWidget->TakeWidget();
		//LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreenAttributes.bAllowEngineTick = true;

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
	}
}
void UASyncLoadingScreen_GIS::OpenLevelWithLoadingScreen(TSubclassOf<UUserWidget> WidgetClass, const TSoftObjectPtr<UWorld> Level)
{
	if (!WidgetClass)
	{
		ensureMsgf(false, TEXT("WidgetClass is nullptr"));
		return;
	}
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreenAttributes;
		LoadingScreenAttributes.WidgetLoadingScreen = Widget->TakeWidget();
		//LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreenAttributes.bAllowEngineTick = true;

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
	}

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
}
