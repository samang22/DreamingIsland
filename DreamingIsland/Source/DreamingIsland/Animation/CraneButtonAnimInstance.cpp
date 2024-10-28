// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CraneButtonAnimInstance.h"

UCraneButtonAnimInstance::UCraneButtonAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ButtonAObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Obj/Crane/CraneButton/Animation/MTG_CreateButton_ButtonAOn.MTG_CreateButton_ButtonAOn'"));
	check(ButtonAObjectFinder.Object);
	ButtonAMontage = ButtonAObjectFinder.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ButtonXObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Obj/Crane/CraneButton/Animation/MTG_CreateButton_ButtonXOn.MTG_CreateButton_ButtonXOn'"));
	check(ButtonXObjectFinder.Object);
	ButtonXMontage = ButtonXObjectFinder.Object;
}

void UCraneButtonAnimInstance::PlayMontage_ButtonAOn()
{
	Montage_Play(ButtonAMontage);
}

void UCraneButtonAnimInstance::PlayMontage_ButtonXOn()
{
	Montage_Play(ButtonXMontage);
}
