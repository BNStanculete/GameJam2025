// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Components/InputComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// First-Person Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimationAsset* IdleAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimationAsset* MovingAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimationAsset* JumpingAnimation;


private:
	void MoveForward(const float value);
	void MoveRight(const float value);
};
