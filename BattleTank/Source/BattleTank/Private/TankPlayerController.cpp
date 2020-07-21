// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h" // so we can implement OnDeath

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();
	if (!ensure (ControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is possessing: %s"), *(ControlledTank->GetName()));
	}

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!ensure (AimingComponent))
    {
		UE_LOG(LogTemp, Error, TEXT("Player Controller can't find AimingComponent at begin play"));
    }
    else
    {
		FoundAimingComponent(AimingComponent);
    }
};

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; };

		// TODO Subscribe our local method to the tank's death event

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; };

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation))// has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}

};

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation) , (ViewportSizeY * CrossHairYLocation));
	
	//De-project the screen position of the crosshair to a wold direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that look direction, and see what we hit (Up to a max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	

	return false;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //Not needed
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection
	);
};

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	};

	return false;
};

void ATankPlayerController::DebugRefillAmmo(int amount)
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; };

	AimingComponent->Ammo += amount;
}