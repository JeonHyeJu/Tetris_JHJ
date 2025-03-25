// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/PlayGameMode.h"
#include "Play/FrameGrid.h"
#include "Play/Block.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalGameInstance.h"

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

	FrameHeight = (Data.Rows + 1) * Data.Radius + FloorHeight;
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

float APlayGameMode::GetZFromBlock(EBlockType _BlockType)
{
	float Z = 1175.f;
	if (_BlockType == EBlockType::LeftRicky || _BlockType == EBlockType::RightRicky)
	{
		Z = 1125.f;
	}

	return Z;
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
	//EBlockType BlockType = StaticCast<EBlockType>(1);	// Temp
	EBlockType BlockType = StaticCast<EBlockType>(Value);

	TSubclassOf<AActor> ActorClass = GameInst->GetBlockClass(BlockType);
	ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(ActorClass);
	if (SpawnedBlock == nullptr)
	{
		return;
	}

	CurBlock = SpawnedBlock;
	CurBlock->SetBlockType(BlockType);

	/*const FInitData& Data = GameInst->GetInitData();
	float H = CurBlock->GetHHalfSize() * Data.Rows;*/

	FVector GenerateLoc(0.f, 0.f, GetZFromBlock(BlockType));
	CurBlock->SetActorLocation(GenerateLoc);

	Blocks.Add(CurBlock);
	CanGenerate = false;
}

void APlayGameMode::SetTetrisLocation(EBlockDirection _Dir)
{
	float Z = CurBlock->GetActorLocation().Z;
	UE_LOG(LogTemp, Warning, TEXT("Z: %f, Height: %f"), Z, FrameHeight);

	if (Z <= FrameHeight)
	{

	}
}

void APlayGameMode::MoveBlock(EBlockDirection _Dir)
{
	if (CurBlock == nullptr)
	{
		return;
	}

	FVector Loc = CurBlock->GetActorLocation();
	float SideSize = CurBlock->GetWHalfSize();

	if (_Dir == EBlockDirection::Left)
	{
		Loc.Y -= SideSize;

		if (Loc.Y <= FrameYStart)
		{
			return;
		}
	}
	else if (_Dir == EBlockDirection::Right)
	{
		Loc.Y += SideSize;

		if (Loc.Y >= FrameYEnd)
		{
			return;
		}
	}
	else if (_Dir == EBlockDirection::Down)
	{
		float Size = CurBlock->GetHHalfSize();
		Loc.Z -= Size;

		if (Loc.Z <= FloorHeight)
		{
			CanGenerate = true;
			return;
		}
	}
	
	CurBlock->Move(_Dir);
	SetTetrisLocation(_Dir);
}