// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/VideoHUD.h"
#include "UI/OpeningWidget.h"
#include "UI/TitleWidget.h"
#include "UI/EndingWidget.h"
#include "UI/LogoWidget.h"

#include "MediaSource.h"
#include "MediaPlayer.h"


AVideoHUD::AVideoHUD()
{
	MediaPlayer = LoadObject<UMediaPlayer>(nullptr, TEXT("/Script/MediaAssets.MediaPlayer'/Game/Assets/Video/MediaPlayer_Opening.MediaPlayer_Opening'"));

	// MediaSource 로드
	OpeningMediaSource = LoadObject<UMediaSource>(nullptr, TEXT("/Script/MediaAssets.FileMediaSource'/Game/Assets/Video/opening.opening'"));
	TitleMediaSource = LoadObject<UMediaSource>(nullptr, TEXT("/Script/MediaAssets.FileMediaSource'/Game/Assets/Video/title.title'"));
	EndingMediaSource = LoadObject<UMediaSource>(nullptr, TEXT("/Script/MediaAssets.FileMediaSource'/Game/Assets/Video/ending.ending'"));
}

void AVideoHUD::BeginPlay()
{
	Super::BeginPlay();
	UClass* WidgetClass = nullptr;
	UClass* LogoWidgetClass = nullptr;
	if (MediaPlayer && OpeningMediaSource)
	{
		WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Opening.UI_Opening_C'"));
		OpeningWidget = CreateWidget<UOpeningWidget>(GetWorld(), WidgetClass);
		OpeningWidget->AddToViewport();

		if (bIsOpening)
		{
			MediaPlayer->OpenSource(OpeningMediaSource);
			LogoWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Logo.UI_Logo_C'"));
			LogoWidget = CreateWidget<ULogoWidget>(GetWorld(), LogoWidgetClass);
			LogoWidget->AddToViewport();
			LogoWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (bIsEnding)
		{
			MediaPlayer->OpenSource(EndingMediaSource);
		}
		else if (bIsTitle)
		{
			MediaPlayer->OpenSource(TitleMediaSource);
			MediaPlayer->SetLooping(true);
			LogoWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Logo.UI_Logo_C'"));
			LogoWidget = CreateWidget<ULogoWidget>(GetWorld(), LogoWidgetClass);
			LogoWidget->AddToViewport();
			LogoWidget->SetVisibility(ESlateVisibility::Visible);
			LogoWidget->SetLogoVisible();
		}
	}
}

void AVideoHUD::Tick(float DeltaTime)
{
	if (bIsOpening)
	{
		if (MediaPlayer->GetDisplayTime().GetTotalSeconds() > 84.f)
		{
			LogoWidget->SetVisibility(ESlateVisibility::Visible);
			LogoWidget->SetLogoVisible();
		}
	}
}
