// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MediaTexture.h"
#include "VideoHUD.generated.h"

class UMediaPlayer;
class UMediaSource;

UCLASS()
class DREAMINGISLAND_API AVideoHUD : public AHUD
{
	GENERATED_BODY()

public:
	AVideoHUD();
protected:
	virtual void BeginPlay() override;
protected:
	TObjectPtr<class UOpeningWidget> OpeningWidget;
	TObjectPtr<class UTitleWidget> TitleWidget;
	TObjectPtr<class UEndingWidget> EndingWidget;

protected:
	TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;
	TObjectPtr<UMediaSource> OpeningMediaSource = nullptr;
	TObjectPtr<UMediaSource> TitleMediaSource = nullptr;
	TObjectPtr<UMediaSource> EndingMediaSource = nullptr;

	UPROPERTY()
	UMediaTexture* MediaTexture;

protected:
	bool bIsOpening = false;
	bool bIsTitle = false;
	bool bIsEnding = false;
public:
	void SetIsOpening(bool bFlag) { bIsOpening = bFlag; }
	void SetIsTitle(bool bFlag) { bIsTitle = bFlag; }
	void SetIsEnding(bool bFlag) { bIsEnding = bFlag; }
};
