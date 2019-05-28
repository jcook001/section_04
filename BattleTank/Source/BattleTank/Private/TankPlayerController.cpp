// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin play called in TankPlayerController"));

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