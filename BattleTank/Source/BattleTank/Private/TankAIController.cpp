// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is possessing: %s"), *(ControlledTank->GetController()->GetName()), *(ControlledTank->GetName()));
	}

	GetPlayerController();
	GetPlayerTank();
};

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

APlayerController* ATankAIController::GetPlayerController() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) 
	{
		UE_LOG(LogTemp, Error, TEXT("AIPlayer: %s cannot find Player Controller"), *(GetControlledTank()->GetController()->GetName()));
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayer: %s has found Player Controller"), *(GetControlledTank()->GetController()->GetName()));
		return PlayerController;
	}
};

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIPlayer: %s cannot find Player Pawn"), *(GetControlledTank()->GetController()->GetName()));
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayer: %s has found Player Pawn: %s"), *(GetControlledTank()->GetController()->GetName()), *(PlayerTank->GetName()));
		return Cast<ATank>(PlayerTank);
	}
};