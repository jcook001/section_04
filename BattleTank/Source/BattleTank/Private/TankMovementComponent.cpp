// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto AITankThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);

	UE_LOG(LogTemp, Warning, TEXT("%s AIForwardDirection: %s, AIForwardIntention: is %s, AITankThrow is %f"), *GetOwner()->GetName(), *TankForwardDirection.ToString(), *AIForwardIntention.ToString(), AITankThrow)

	IntendMoveForward(AITankThrow);

    auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;

    IntendTurnRight(RightThrow);
}
