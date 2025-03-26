// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/PlayGameMode.h"
#include "Play/FrameGrid.h"
#include "Play/Block.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalGameInstance.h"

APlayGameMode::~APlayGameMode()
{
	Tetris.Empty();
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() == nullptr)
	{
		return;
	}
}

void APlayGameMode::LazyInit()
{
	UGlobalGameInstance* GameInst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInst == nullptr)
	{
		return;
	}

	const FInitData& Data = GameInst->GetInitData();
	InitData = Data;

	Tetris.Reserve(Data.Rows);

	for (int i = 0; i < Data.Rows; ++i)
	{
		TArray<bool> Temp;
		Temp.Reserve(Data.Cols);
		for (int j = 0; j < Data.Cols; ++j)
		{
			Temp.Add(false);
		}

		Tetris.Add(Temp);
	}

	FrameZEnd = Data.Rows * Data.Radius;
	FrameYEnd = FMath::CeilToFloat((Data.Cols - 1) * Data.Radius * .5f);
	FrameYStart = -FrameYEnd;
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 하나만 존재
	static float ElapsedSecs = 0.f;

	if (!IsLazyInited)
	{
		IsLazyInited = true;
		LazyInit();
	}

	if (CanGenerate)
	{
		GenerateBlock();
	}
}

void APlayGameMode::GenerateBlock()
{
	static const int Min = 0;
	static const int Max = StaticCast<int>(EBlockType::Size) - 1;

	if (CanGenerate == false)
	{
		return;
	}

	if (GetWorld() == nullptr)
	{
		return;
	}

	UGlobalGameInstance* GameInst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInst == nullptr)
	{
		return;
	}

	int Value = FMath::RandRange(Min, Max);
	EBlockType BlockType = StaticCast<EBlockType>(0);	// Temp
	//EBlockType BlockType = StaticCast<EBlockType>(Value);

	int Mid = StaticCast<int>(InitData.Cols * .5f);

	TSubclassOf<AActor> ActorClass = GameInst->GetBlockClass(BlockType);
	ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(ActorClass);
	if (SpawnedBlock == nullptr)
	{
		return;
	}

	CurBlock = SpawnedBlock;
	CurBlock->Y = 1;
	CurBlock->X = Mid;

	FVector GenerateLoc(0.f, 0.f, FrameZEnd);
	if (BlockType == EBlockType::Hero)
	{
		GenerateLoc.Z -= 100.f;
		CurBlock->Y = 2;
		CurBlock->X = Mid;
	}
	
	CurBlock->SetBlockType(BlockType);
	CurBlock->SetActorLocation(GenerateLoc);

	Blocks.Add(CurBlock);
	CanGenerate = false;
}

bool APlayGameMode::IsOccupied(const TPair<int, int>& _Pair)
{
	int IdxI = _Pair.Key;
	int IdxJ = _Pair.Value;
	if (IdxI < 0 || IdxJ < 0)
	{
		return true;
	}
	if (IdxI >= InitData.Rows || IdxJ >= InitData.Cols)
	{
		return true;
	}
	if (Tetris[IdxI][IdxJ])
	{
		return true;
	}

	return false;
}

bool APlayGameMode::CanMove(int I, int J, int _Degree)
{
	TArray<TPair<int, int>> Idxs = CurBlock->GetBlockIndices(I, J, _Degree);

	bool IsAllPass = true;
	for (int i = 0, size = Idxs.Num(); i < size; ++i)
	{
		if (IsOccupied(Idxs[i]))
		{
			IsAllPass = false;
			break;
		}
	}

	return IsAllPass;
}

bool APlayGameMode::SetTetris(int I, int J)
{
	TArray<TPair<int, int>> Idxs = CurBlock->GetBlockIndices(I, J);

	int Rows = Tetris.Num();
	for (int i = 0, size = Idxs.Num(); i < size; ++i)
	{
		if (Idxs[i].Key >= Rows)
		{
			return false;
		}
		if (Idxs[i].Value >= Tetris[i].Num())
		{
			return false;
		}

		Tetris[Idxs[i].Key][Idxs[i].Value] = true;
	}

	return true;
}

void APlayGameMode::UpdateTetrisLocation(int I, int J)
{
	EBlockType BlockType = CurBlock->GetBlockType();

	SetTetris(I, J);

	Tetris;
	int a = 0;
}

void APlayGameMode::MoveBlock(EBlockDirection _Dir)
{
	if (CurBlock == nullptr)
	{
		return;
	}

	int I = CurBlock->Y;
	int J = CurBlock->X;

	if (_Dir == EBlockDirection::Left)
	{
		J -= 1;
	}
	else if (_Dir == EBlockDirection::Right)
	{
		J += 1;
	}
	else if (_Dir == EBlockDirection::Down)
	{
		I += 1;
	}

	if (CanMove(I, J))
	{
		CurBlock->Move((InitData.Rows - 1) - I, J, FrameYStart);
		CurBlock->Y = I;
		CurBlock->X = J;
	}
	else
	{
		if (_Dir == EBlockDirection::Down)
		{
			CanGenerate = true;
			UpdateTetrisLocation(I - 1, J);
		}
	}
}

void APlayGameMode::RotateBlock()
{
	if (CurBlock == nullptr)
	{
		return;
	}

	int I = CurBlock->Y;
	int J = CurBlock->X;

	int Degree = CurBlock->GetFutureDegree();
	if (CanMove(I, J, Degree))
	{
		CurBlock->Rotate();
	}
}