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
		for (int j = 0; j < Data.Cols; ++j)
		{
			Temp.Add(false);
		}

		Tetris.Add(Temp);
	}

	FrameHeight = Data.Rows * Data.Radius;
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 하나만 존재
	static float ElapsedSecs = 0.f;
	static bool IsLazyInited = false;

	if (!IsLazyInited)
	{
		IsLazyInited = true;
		LazyInit();
	}

	ElapsedSecs += _DeltaTime;
	if (ElapsedSecs >= .5f)
	{
		ElapsedSecs = 0.f;
		//CanGenerate = true;		// Temp
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
	EBlockType BlockType = StaticCast<EBlockType>(1);	// Temp
	//EBlockType BlockType = StaticCast<EBlockType>(Value);

	TSubclassOf<AActor> ActorClass = GameInst->GetBlockClass(BlockType);
	ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(ActorClass);
	if (SpawnedBlock == nullptr)
	{
		return;
	}

	FVector GenerateLoc(0.f, 0.f, GetZFromBlock(BlockType));

	SpawnedBlock->SetActorLocation(GenerateLoc);
	SpawnedBlock->SetBlockType(BlockType);

	Blocks.Add(SpawnedBlock);

	CurBlock = SpawnedBlock;
	CanGenerate = false;
}

void APlayGameMode::SetTetrisLocation(EBlockDirection _Dir)
{

}

void APlayGameMode::MoveBlock(EBlockDirection _Dir)
{
	if (CurBlock == nullptr)
	{
		return;
	}

	CurBlock->Move(_Dir);

	float Z = CurBlock->GetActorLocation().Z;

	UE_LOG(LogTemp, Warning, TEXT("Z: %f, Height: %f"), Z, FrameHeight);
	//SetTetrisLocation(_Dir);
}