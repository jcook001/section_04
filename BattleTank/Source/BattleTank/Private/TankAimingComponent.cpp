// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    //So that first fire is delayed when starting the game
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (Ammo <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds * ReloadTimeMultiplier)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    if (!ensure (BarrelToSet)) { return; }
    Barrel = BarrelToSet;

    if (!ensure (TurretToSet)) { return; }
    Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }

    auto BarrelForward = Barrel->GetForwardVector();

    return !BarrelForward.Equals(AimDirection, 0.1);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure (Barrel && Turret)) { UE_LOG(LogTemp, Error, TEXT("Turret or Barrel are missing from %s!"), *GetOwner()->GetName()); return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));
	FCollisionResponseParams DefaultResponse;
	TArray < AActor* > ActorsToIgnore;

	//Calculate the out launch velocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, //if false choose low arc
		1, //collision radius
		0, //override gravity, 0 is no override
		ESuggestProjVelocityTraceOption::DoNotTrace,
		DefaultResponse,
		ActorsToIgnore,
		false //draw debug
	);

	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(AimDirection);

	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s does not have an aim solution"), *GetOwner()->GetName());
    }
};

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
}

void UTankAimingComponent::RotateTurretTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

    //always Yaw the shortest way (except it doesn't work :( )
    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

void UTankAimingComponent::Fire()
{
    if (!ensure(Barrel && ProjectileBlueprint)) { return; }

    if (FiringState != EFiringState::Reloading && Ammo > 0)
    {
        //spawn a projectile at the socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("BarrelEnd")),
            Barrel->GetSocketRotation(FName("BarrelEnd"))
            );

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        Ammo--;
    }
}

