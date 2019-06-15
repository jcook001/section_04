// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Engine/World.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is possessing: %s"), *(ControlledTank->GetName()));
	}
};

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; };

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation))// has "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString())
			//TODO Tell controlled tank to aim at this point
	}

};

//Get world location of linetrace through crosshair, true if hits landscape
const bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	//find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation) , (ViewportSizeY * CrossHairYLocation));
	
	//De-project the screen position of the crosshair to a wold direction
	//Line-trace along that look direction, and see what we hit (Up to a max range)

	return true;

}