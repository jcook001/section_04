// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
};

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank && ControlledTank)
	{
		//TODO Move towards the player

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		ControlledTank->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI or player are not possessing a tank!"));
	}
};