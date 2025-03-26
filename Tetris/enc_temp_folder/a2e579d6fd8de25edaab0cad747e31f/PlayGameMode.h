// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalData.h"
#include "GameFramework/GameMode.h"
#include "PlayGameMode.generated.h"

USTRUCT()
struct FBlockData
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Block = nullptr;

	int I = 0;
	int J = 0;
	bool IsDestroied = false;
};

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
	void RotateBlock();

private:
	void LazyInit();
	void GenerateBlock();
	void UpdateTetrisLocation(int I, int J);
	bool IsOccupied(const TPair<int, int>& _Pair);
	bool CanMove(int I, int J, int _Degree=0);
	bool SetTetris(int I, int J);
	void TurnToStone();
	void CheckToStone();

	bool IsTouchedFloor = false;
	bool IsLazyInited = false;
	bool CanGenerate = true;

	float FrameYStart = 0.f;
	float FrameYEnd = 0.f;
	float FrameZEnd = 0.f;
	float FrameZStart = 100.f;
	const float DIAMETER = 100.f;	// Temp

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (AllowPrivateAccess="true"))
	TSubclassOf<AActor> OneBlock = nullptr;

	UPROPERTY()
	TArray<class ABlock*> Blocks;

	UPROPERTY()
	TArray<FBlockData> StaticBlocks;

	UPROPERTY()
	class ABlock* CurBlock = nullptr;

	TArray<TArray<bool>> Tetris;
	FInitData InitData;
};
