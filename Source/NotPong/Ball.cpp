// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Characters/Paddle.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector Direction = PlayerLocation - GetActorLocation();
	Direction.Normalize();

	Mesh->AddImpulse(Direction * 200.f);

	PositionLastFrame = GetActorLocation();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TestCollision();
}

void ABall::TestCollision()
{
	// The object types we want to collide with
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	// Will be populated if we hit something
	FHitResult HitResult;

	// Actual trace
	// Some hard coded values like radius is not a good practice :))))
	bool bWasBlockingHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(), PositionLastFrame, GetActorLocation(),
		33.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None,
		HitResult, true);

	if (bWasBlockingHit)
	{
		float dot = FVector::DotProduct(Mesh->GetComponentVelocity(), HitResult.Normal);
		FVector Direction = Mesh->GetComponentVelocity() - (2.f * dot * HitResult.Normal);
		Direction.Normalize(); // Redundant, remove to avoid multiplying the velocity size back in

		FVector NewVelocity = Direction * Mesh->GetComponentVelocity().Size() + 10.f;
		NewVelocity.X = 0; // Removing movement from the X axis

		Mesh->SetPhysicsLinearVelocity(NewVelocity, false);

		// To avoid hitting the same object multiple times
		ActorsToIgnore.Emplace(HitResult.Actor.Get());
	}
	else
	{
		ActorsToIgnore.Empty();
	}

	PositionLastFrame = GetActorLocation();
}
