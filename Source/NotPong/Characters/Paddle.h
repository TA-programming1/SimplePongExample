// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class NOTPONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveUp(float Value);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Paddle | Camera")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Paddle | Camera")
	class UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, Category = "Paddle | Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Paddle | Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Paddle | Movement")
	class UFloatingPawnMovement* FloatingPawnMovement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
