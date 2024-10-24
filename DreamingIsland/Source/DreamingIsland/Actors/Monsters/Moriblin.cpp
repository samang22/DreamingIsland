// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Monsters/Moriblin.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

float CalculateAngleBetweenVectors(const FVector& A, const FVector& B) {
	// Calculate dot product
	float DotProduct = FVector::DotProduct(A, B);

	// 두 벡터의 크기를 계산
	float MagnitudeA = A.Size();
	float MagnitudeB = B.Size();

	// 코사인 값 계산
	float CosTheta = DotProduct / (MagnitudeA * MagnitudeB);

	// 각도 계산 (라디안)
	float AngleRadians = FMath::Acos(CosTheta);

	// 라디안을 각도로 변환
	return FMath::RadiansToDegrees(AngleRadians);
}

float AMoriblin::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }
	
	// check if Link is infront of Moriblin
	FVector MoriblinToLinkDir = DamageCauser->GetActorLocation() - this->GetActorLocation();
	MoriblinToLinkDir.Z = 0.f;
	MoriblinToLinkDir.Normalize();
	float Degree = CalculateAngleBetweenVectors(MoriblinToLinkDir, this->GetActorForwardVector());


	if (Degree < MORIBLIN_SHIELD_DEGREE)
	{
		// Turn to Link
		SetActorRotation(MoriblinToLinkDir.Rotation().Quaternion());
		PlayMontage(MONSTER_MONTAGE::GUARD);
		return 0.f;
	}



	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}



	if (StatusComponent->IsDie() && MonsterData->DeadMontage)
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		PlayMontage(MONSTER_MONTAGE::DEAD);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			MonsterData->DeadMontage->GetPlayLength() - 0.1f, false);
	}
	else if (!StatusComponent->IsDie() && MonsterData->DamageMontage)
	{
		PlayMontage(MONSTER_MONTAGE::DAMAGE);
	}

	return 0.0f;
}
