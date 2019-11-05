// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector HitLocation)
{
    if (!TankAimingComponent) { UE_LOG(LogTemp, Error, TEXT("TankAimingComponent is missing!")); return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::InitialiseAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		//spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Pew Pew"));
		LastFireTime = FPlatformTime::Seconds();
	}
}

bool ATank::GetAIPlayerCanShoot() const
{
	return AIPlayerCanShoot;
}