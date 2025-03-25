// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalData.h"
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

public:
	void MoveBlock(EBlockDirection _Dir);

private:
	void LazyInit();
	float GetZFromBlock(EBlockType _BlockType);
	void GenerateBlock();
	void SetTetrisLocation(EBlockDirection _Dir);

	bool IsTouchedFloor = false;
	bool IsLazyInited = false;
	bool CanGenerate = true;

	float FrameYStart = 0.f;
	float FrameYEnd = 0.f;
	float FrameHeight = 0.f;
	float FloorHeight = 75.f;

	UPROPERTY()
	TArray<AActor*> Blocks;

	UPROPERTY()
	class ABlock* CurBlock = nullptr;

	UPROPERTY()
	TArray<TArray<bool>> Tetris;
};
