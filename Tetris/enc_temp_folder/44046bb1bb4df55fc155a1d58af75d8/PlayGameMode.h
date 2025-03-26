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

	~APlayGameMode();
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

public:
	void MoveBlock(EBlockDirection _Dir);

private:
	void LazyInit();
	void GenerateBlock();
	void UpdateTetrisLocation(int I, int J);
	bool IsOccupied(const TPair<int, int>& _Pair);
	bool CanMove(int I, int J);
	void SetTetris(int I, int J);

	bool IsTouchedFloor = false;
	bool IsLazyInited = false;
	bool CanGenerate = true;

	float FrameYStart = 0.f;
	float FrameYEnd = 0.f;
	float FrameZEnd = 0.f;
	float FrameZStart = 100.f;
	const float DIAMETER = 100.f;	// Temp

	UPROPERTY()
	TArray<AActor*> Blocks;

	UPROPERTY()
	class ABlock* CurBlock = nullptr;

	TArray<TArray<bool>> Tetris;

	FInitData InitData;
};
