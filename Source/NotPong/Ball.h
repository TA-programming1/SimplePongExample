// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class NOTPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ball | Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY() 
	TArray<AActor*> ActorsToIgnore{};

	FVector PositionLastFrame{};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TestCollision();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
