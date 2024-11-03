
#include "GameInstance/DreamingIsland_GIS.h"
#include "GameInstance/MyLevelStreamingDynamic.h"
#include "Actors/Link/Link.h"
#include "Components/StatusComponent/LinkStatusComponent.h"
#include "Engine/LevelStreamingDynamic.h"

void UDreamingIsland_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UDreamingIsland_GIS::Deinitialize()
{
}

void UDreamingIsland_GIS::SaveLinkData()
{
    UWorld* World = GetWorld();
    if (World)
    {
        // 첫 번째 PlayerController 가져오기
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            // PlayerController에서 Pawn 가져오기
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

void UDreamingIsland_GIS::LoadPersistentLevel(UWorld* World, const FString& LevelName)
{
    if (!World) return;

    // 레벨 로드 위치와 회전을 설정합니다.
    FVector Location = FVector::ZeroVector;
    FRotator Rotation = FRotator::ZeroRotator;

    //UMyLevelStreamingDynamic* LoadedLevel = UMyLevelStreamingDynamic::LoadLevelInstance(
    //    World,
    //    LevelName,
    //    Location,
    //    Rotation,
    //    true  // Blocking load를 설정할지 여부, 여기서는 비동기로 로드하도록 설정
    //);

    //if (LoadedLevel)
    //{
    //    LoadedLevel->bShouldBeLoaded = true;   // 항상 로드 상태 유지
    //    LoadedLevel->bShouldBeVisible = true;  // 가시성 설정
    //}
}
