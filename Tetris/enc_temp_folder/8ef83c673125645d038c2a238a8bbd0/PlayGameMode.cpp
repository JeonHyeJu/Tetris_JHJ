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

	TSubclassOf<AActor> ActorClass = GameInst->GetBlockClass(BlockType);
	ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(ActorClass);
	if (SpawnedBlock == nullptr)
	{
		return;
	}

	CurBlock = SpawnedBlock;
	CurBlock->SetBlockType(BlockType);
	CurBlock->SetActorLocation(FVector(0.f, 0.f, FrameZEnd));

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

bool APlayGameMode::CanMove(int I, int J)
{
	TArray<TPair<int, int>> Idxs = CurBlock->GetBlockIndices(I, J);

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

void APlayGameMode::SetTetris(int I, int J)
{
	TArray<TPair<int, int>> Idxs = CurBlock->GetBlockIndices(I, J);

	for (int i = 0, size = Idxs.Num(); i < size; ++i)
	{
		Tetris[Idxs[i].Key][Idxs[i].Value] = true;
	}
}

void APlayGameMode::UpdateTetrisLocation(int I, int J)
{
	UE_LOG(LogTemp, Warning, TEXT("%d, %d"), I, J);

	// TODO: Subtract
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

	FVector DstLoc = CurBlock->GetActorLocation();
	float SideSize = CurBlock->GetWHalfSize();

	if (_Dir == EBlockDirection::Left)
	{
		DstLoc.Y -= SideSize;

		/*if (Loc.Y <= FrameYStart)
		{
			return;
		}*/
	}
	else if (_Dir == EBlockDirection::Right)
	{
		DstLoc.Y += SideSize;

		/*if (Loc.Y >= FrameYEnd)
		{
			return;
		}*/
	}
	else if (_Dir == EBlockDirection::Down)
	{
		float Size = CurBlock->GetHHalfSize();
		DstLoc.Z -= Size;

		/*if (Loc.Z <= FrameZStart)
		{
			CanGenerate = true;
			UpdateTetrisLocation();
			return;
		}*/
	}

	int I = InitData.Rows - StaticCast<int>((DstLoc.Z - FrameZStart) / DIAMETER) - 1;
	int J = StaticCast<int>((DstLoc.Y - FrameYStart) / DIAMETER);

	if (CanMove(I, J))
	{
		CurBlock->Move(_Dir);
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