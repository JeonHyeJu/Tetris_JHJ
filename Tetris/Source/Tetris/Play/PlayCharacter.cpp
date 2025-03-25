// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/PlayCharacter.h"

APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayCharacter::OnMove(const FVector2D& _Vec)
{
	UE_LOG(LogTemp, Log, TEXT("%f %f"), _Vec.X, _Vec.Y);
	AddMovementInput(FVector(_Vec.X, _Vec.Y, 0.f));
}
