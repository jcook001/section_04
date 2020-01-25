// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Core/Public/Math/Vector.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//No need to protect points as added at construction
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachTo(CollisionMesh);
    LaunchBlast->bAutoActivate = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComponent->Activate();
}

