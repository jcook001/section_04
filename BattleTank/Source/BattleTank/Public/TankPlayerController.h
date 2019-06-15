// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual ATank* GetControlledTank() const;

	virtual void AimTowardsCrosshair();

	const bool GetSightRayHitLocation(FVector& OutHitLocation);

	FHitResult HitLocation;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
};
