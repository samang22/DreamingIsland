// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/FishingPondGameModeBase.h"
#include "Actors/Link/FishingLinkController.h"

AFishingPondGameModeBase::AFishingPondGameModeBase()
{
	PlayerControllerClass = AFishingLinkController::StaticClass();
	{
		static ConstructorHelpers::FClassFinder<APawn> ClassFinder(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Link/BP_FishingLink.BP_FishingLink_C'"));
		check(ClassFinder.Class);
		DefaultPawnClass = ClassFinder.Class;
	}
}
