// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating the First-Person Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, -24.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// These make the camera rotate with mouse input
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;

	// Disable character movement's rotation so the controller has full control
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if jumping
	if (GetCharacterMovement()->IsFalling())
	{
		if (GetMesh()->GetAnimationMode() != EAnimationMode::AnimationSingleNode ||
			GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode && GetMesh()->GetSingleNodeInstance()->GetAnimationAsset() != JumpingAnimation)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			GetMesh()->PlayAnimation(JumpingAnimation, true);  // loop true or false depends on your jump anim
		}
	}
	else
	{
		float Speed = GetVelocity().Size();

		if (Speed > 0.1f) // moving
		{
			if (GetMesh()->GetAnimationMode() != EAnimationMode::AnimationSingleNode ||
				GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode && GetMesh()->GetSingleNodeInstance()->GetAnimationAsset() != MovingAnimation)
			{
				GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
				GetMesh()->PlayAnimation(MovingAnimation, true);
			}
		}
		else // idle
		{
			if (GetMesh()->GetAnimationMode() != EAnimationMode::AnimationSingleNode ||
				GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode && GetMesh()->GetSingleNodeInstance()->GetAnimationAsset() != IdleAnimation)
			{
				GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
				GetMesh()->PlayAnimation(IdleAnimation, true);
			}
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Camera rotation
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void APlayerCharacter::MoveForward(const float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::MoveRight(const float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}