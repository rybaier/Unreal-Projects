// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// FString Name = GetName(); function within Unreal that allows Variable to grab the name
	// add * in front of string variable for Unreal Editor see line 23 and line 51
	// UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name)
// Below is the syntax for writing to the UE log for debugging
// Display is one of numerous options for LogTemp
	// UE_LOG(LogTemp, Display, TEXT("your message here"));
		// UE_LOG(LogTemp, Display, TEXT("Congfigured Moved Distance %f"), MoveDistance);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	// Move Platform forwards
		// get current location 
	FVector CurrentLocation = GetActorLocation();
		// add vector to that location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;	
		// set the location 
	SetActorLocation(CurrentLocation);	
	
		// reverse direction of motion if gone to far
	if (ShouldPlatformReturn())
	{

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}	
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}
// // send platform back if gone to far
		// check how far we.ve moved
	// FString Name = GetName();
	// float OverShoot = GetDistanceMoved() - MoveDistance;
	// UE_LOG(LogTemp, Display, TEXT(" %s overshot by %f"), *Name, OverShoot);