// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth); //clamp damage so health does not go below 0

    this->CurrentHealth -= DamageToApply;

    if (CurrentHealth <= 0) {
        UE_LOG(LogTemp, Warning, TEXT("%s has died"), *this->GetName());
    }

    return DamageToApply;
}
