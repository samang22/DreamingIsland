// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/EndingGameModeBase.h"
#include "Actors/Default/VideoHUD.h"

AEndingGameModeBase::AEndingGameModeBase()
{
	HUDClass = AVideoHUD::StaticClass();
}

void AEndingGameModeBase::StartPlay()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        // PlayerController에서 HUD 객체 가져오기
        AVideoHUD* HUD = Cast<AVideoHUD>(PlayerController->GetHUD());
        HUD->SetIsEnding(true);
    }
    Super::StartPlay();
}

