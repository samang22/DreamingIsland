// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/OpeningGameModeBase.h"
#include "Actors/Default/VideoHUD.h"

AOpeningGameModeBase::AOpeningGameModeBase()
{
	HUDClass = AVideoHUD::StaticClass();
}

void AOpeningGameModeBase::StartPlay()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        // PlayerController에서 HUD 객체 가져오기
        AVideoHUD* HUD = Cast<AVideoHUD>(PlayerController->GetHUD());
        HUD->SetIsOpening(true);
    }
    Super::StartPlay();
}

