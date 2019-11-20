// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h" // this needs to stay at the top
#include "TankAimingComponent.h"
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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

    if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(
		PlayerTank,
		AcceptanceRadius
		);

	//Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready
    AimingComponent->Fire(); //TODO add debug option check

};