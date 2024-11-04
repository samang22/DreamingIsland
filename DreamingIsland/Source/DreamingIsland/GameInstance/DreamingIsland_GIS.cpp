
#include "GameInstance/DreamingIsland_GIS.h"
#include "GameInstance/MyLevelStreamingDynamic.h"
#include "Actors/Link/Link.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameInstance/Conversation_GIS.h"

void UDreamingIsland_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
    LinkData.Rupee = 200;
}

void UDreamingIsland_GIS::Deinitialize()
{
}

void UDreamingIsland_GIS::SaveLinkData()
{
    UWorld* World = GetWorld();
    if (World)
    {
        // PlayerController 
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            // PlayerController
            ALink* Link = Cast<ALink>(PlayerController->GetPawn());
            if (Link)
            {
                const ULinkStatusComponent* StatusComponent = Link->GetStatusComponent();
                LinkData.LinkToolEquipStatus = StatusComponent->GetEntireToolEquipStatus();
                LinkData.Rupee = StatusComponent->GetRupee();
                LinkData.Arrow = StatusComponent->GetArrow();
                LinkData.Bomb = StatusComponent->GetBomb();
            }
            else
            {
                check(false);
            }
        }
    }
}

void UDreamingIsland_GIS::LoadLinkData(ALink* Link) const
{
	ULinkStatusComponent* StatusComponent = Link->GetStatusComponent();
	StatusComponent->SetOnToolEquipStatus(LinkData.LinkToolEquipStatus);
	StatusComponent->SetRupee(LinkData.Rupee);
	StatusComponent->SetArrow(LinkData.Arrow);
	StatusComponent->SetBomb(LinkData.Bomb);
}