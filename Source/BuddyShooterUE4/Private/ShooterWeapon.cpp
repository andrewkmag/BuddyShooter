// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterWeapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
AShooterWeapon::AShooterWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set mesh component of weapon
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AShooterWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Traces world from pawn's eyes to crosshair location
void AShooterWeapon::PullTrigger()
{
	// Check who owns the current weapon
	AActor* CurrentOwner = GetOwner();

	if (CurrentOwner)
	{
		// Gather data of Actor's Eyes viewpoint
		FVector EyeLocation;
		FRotator EyeRotation;
		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		// Initialize and calculate the distance of how far the gun can trace
		FVector EndOfTrace = EyeLocation + (EyeRotation.Vector() * 10000);

		// Create query parameters on collision to trace each individual triangle 
		// of the mesh that is being hit to get more precise hit result data
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		// Initialize struct to gather hit data / trace results
		// and perform the line trace
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, EndOfTrace, ECC_Visibility))
		{
			// Hit detected
		}

		DrawDebugLine(GetWorld(), EyeLocation, EndOfTrace, FColor::White, false, 1.0f, 0, 1.0f);
	}

	

}

// Called every frame
void AShooterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

