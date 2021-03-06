// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
* TankTrack is used to set maximum driving force, and to apply forces to the tank.
**/
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	//Sets throttle to a value between 0 and 1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 20000000; //assume 40 tonne tank and 1g acceleration tank starts to fly if force is much higher than this

private:
    UTankTrack();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    void ApplySidewaysForce();

    void DriveTrack();

    float CurrentThrottle = 0;
};
