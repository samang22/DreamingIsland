// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/TitleGameModeBase.h"
#include "Actors/Default/VideoHUD.h"

ATitleGameModeBase::ATitleGameModeBase()
{
	HUDClass = AVideoHUD::StaticClass();
}

void ATitleGameModeBase::StartPlay()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        // PlayerController에서 HUD 객체 가져오기
        AVideoHUD* HUD = Cast<AVideoHUD>(PlayerController->GetHUD());
        HUD->SetIsTitle(true);
    }
    Super::StartPlay();
}
