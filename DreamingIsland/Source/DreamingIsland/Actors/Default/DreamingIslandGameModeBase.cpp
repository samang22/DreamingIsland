// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Default/DreamingIslandGameModeBase.h"
#include "Actors/Link/LinkController.h"

ADreamingIslandGameModeBase::ADreamingIslandGameModeBase()
{
	PlayerControllerClass = ALinkController::StaticClass();
	{
		static ConstructorHelpers::FClassFinder<APawn> ClassFinder(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Link/BP_Link.BP_Link_C'"));
		check(ClassFinder.Class);
		DefaultPawnClass = ClassFinder.Class;
	}
}
