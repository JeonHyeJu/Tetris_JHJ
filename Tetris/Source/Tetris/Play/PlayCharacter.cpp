// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/PlayCharacter.h"
#include "Play/PlayGameMode.h"

APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayCharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ElapsedMoveSecs += _DeltaTime;
	if (ElapsedMoveSecs >= MOVE_SEC)
	{
		ElapsedMoveSecs = 0.f;
		CanMove = true;
	}
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

EBlockDirection APlayCharacter::GetDirection(const FVector2D& _Vec)
{
	static const float EPS = 1e-2;
	EBlockDirection Dir = EBlockDirection::None;

	if (FMath::IsNearlyEqual(_Vec.X, 1.f, EPS))
	{
		Dir = EBlockDirection::Up;	// Temp
	}
	else if (FMath::IsNearlyEqual(_Vec.X, -1.f, EPS))
	{
		Dir = EBlockDirection::Down;
	}

	if (FMath::IsNearlyEqual(_Vec.Y, 1.f, EPS))
	{
		Dir = EBlockDirection::Right;
	}
	else if (FMath::IsNearlyEqual(_Vec.Y, -1.f, EPS))
	{
		Dir = EBlockDirection::Left;
	}

	return Dir;
}

void APlayCharacter::OnMove(const FVector2D& _Vec)
{
	if (CanMove == false)
	{
		return;
	}

	//UE_LOG(LogTemp, Log, TEXT("%f %f"), _Vec.X, _Vec.Y);
	//AddMovementInput(FVector(_Vec.X, _Vec.Y, 0.f));

	APlayGameMode* GameMode = Cast<APlayGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
	{
		return;
	}

	GameMode->MoveBlock(GetDirection(_Vec));
	CanMove = false;
}
