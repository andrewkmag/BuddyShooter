// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup 3rd Person follow camera parameters:
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	// Set Camera Position from character using arbitrary values
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->SocketOffset.X = 92.f;
	SpringArmComp->SocketOffset.Y = 50.f;
	SpringArmComp->SocketOffset.Z = -14.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Enable/disable ability to crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//================================================================//
//==============   Movement Functions BEGIN   ====================//
//================================================================//
void AShooterCharacter::MoveForward(float direction)
{
	AddMovementInput(GetActorForwardVector() * direction);
}

void AShooterCharacter::MoveSideways(float direction)
{
	AddMovementInput(GetActorRightVector() * direction);
}

void AShooterCharacter::BeginCrouch()
{
	Crouch();
}

void AShooterCharacter::EndCrouch()
{
	UnCrouch();
}
//================================================================//
//===============   Movement Functions END   =====================//
//================================================================//


// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis Movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &AShooterCharacter::MoveSideways);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AShooterCharacter::AddControllerYawInput);

	// Bind Action inputs
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AShooterCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AShooterCharacter::EndCrouch);

}

