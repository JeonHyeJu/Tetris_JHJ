// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayCharacter.generated.h"

UCLASS()
class TETRIS_API APlayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnMove(const FVector2D& _Vec);

protected:
	virtual void BeginPlay() override;

};
