
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
        // ù ��° PlayerController ��������
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            // PlayerController���� Pawn ��������
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

    // ���� �ε� ��ġ�� ȸ���� �����մϴ�.
    FVector Location = FVector::ZeroVector;
    FRotator Rotation = FRotator::ZeroRotator;

    //UMyLevelStreamingDynamic* LoadedLevel = UMyLevelStreamingDynamic::LoadLevelInstance(
    //    World,
    //    LevelName,
    //    Location,
    //    Rotation,
    //    true  // Blocking load�� �������� ����, ���⼭�� �񵿱�� �ε��ϵ��� ����
    //);

    //if (LoadedLevel)
    //{
    //    LoadedLevel->bShouldBeLoaded = true;   // �׻� �ε� ���� ����
    //    LoadedLevel->bShouldBeVisible = true;  // ���ü� ����
    //}
}
