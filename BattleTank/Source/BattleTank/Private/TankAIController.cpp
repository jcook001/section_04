// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h" // this needs to stay at the top
#include "TankPlayerController.h"
#include "TankMovementComponent.h"
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
		//Move towards the player
		MoveToActor(
			PlayerTank,
			AcceptanceRadius
			);

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		//check debug option
		if (PlayerTank->GetAIPlayerCanShoot())
		{
			ControlledTank->Fire(); //TODO renenable this
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI or player are not possessing a tank!"));
	}
};