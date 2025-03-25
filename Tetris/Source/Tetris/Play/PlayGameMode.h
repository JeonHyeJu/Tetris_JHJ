// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API APlayGameMode : public AGameMode
{
	GENERATED_BODY()
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const float GEN_SEC = 1.f;

	void GenerateBlock();

	UPROPERTY()
	TArray<AActor*> Blocks;
};
