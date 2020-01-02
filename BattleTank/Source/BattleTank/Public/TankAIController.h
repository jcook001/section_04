// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000.f;

private:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
