// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/HouseGameModeBase.h"
#include "Actors/LinkController.h"
#include "Actors/Default/DefaultHUD.h"




AHouseGameModeBase::AHouseGameModeBase()
{
	PlayerControllerClass = ALinkController::StaticClass();
	{
		static ConstructorHelpers::FClassFinder<APawn> ClassFinder(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Link/BP_LinkInHouse.BP_LinkInHouse_C'"));
		check(ClassFinder.Class);
		DefaultPawnClass = ClassFinder.Class;
	}

	HUDClass = ADefaultHUD::StaticClass();
}
