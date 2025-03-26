// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Block.h"
#include "Engine/HitResult.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	BlockMesh->SetupAttachment(RootComponent);
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EBlockType ABlock::GetBlockType() const
{
	return BlockType;
}

void ABlock::SetBlockType(EBlockType _Type)
{
	BlockType = _Type;
}

TArray<TPair<int, int>> ABlock::GetBlockIndices(int I, int J)
{
	TArray<TPair<int, int>> Idxs;
	Idxs.Reserve(4);

	if (BlockType == EBlockType::Hero)
	{
		for (int i = -2; i < 2; ++i)
		{
			Idxs.Add(TPair<int, int>{ I + i, J });
		}
	}
	else if (BlockType == EBlockType::Teewee)
	{
		Idxs.Add(TPair<int, int>{ I - 1, J });
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I, J - 1 });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
	}
	else if (BlockType == EBlockType::SmashBody)
	{
		Idxs.Add(TPair<int, int>{ I - 1, J + 1 });
		Idxs.Add(TPair<int, int>{ I - 1, J + 2 });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
		Idxs.Add(TPair<int, int>{ I, J + 2 });
	}
	else if (BlockType == EBlockType::LeftRicky)
	{
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I - 1, J });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
		Idxs.Add(TPair<int, int>{ I, J + 2 });
	}
	else if (BlockType == EBlockType::RightRicky)
	{

	}
	else if (BlockType == EBlockType::Cleveland)
	{

	}
	else if (BlockType == EBlockType::RhodeIsland)
	{

	}

	return Idxs;
}

float ABlock::GetWHalfSize() const
{
	float Size = 0.f;
	if (BlockType == EBlockType::Hero)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::Teewee)
	{
		Size = MOVE_SPACE + MOVE_SPACE * .5f;
	}
	else if (BlockType == EBlockType::SmashBody)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::LeftRicky)
	{
		Size = MOVE_SPACE + MOVE_SPACE * .5f;
	}
	else if (BlockType == EBlockType::RightRicky)
	{
		Size = MOVE_SPACE + MOVE_SPACE * .5f;
	}
	else if (BlockType == EBlockType::Cleveland)
	{
		Size = MOVE_SPACE + MOVE_SPACE * .5f;
	}
	else if (BlockType == EBlockType::RhodeIsland)
	{
		Size = MOVE_SPACE + MOVE_SPACE * .5f;
	}

	return Size;
}

float ABlock::GetHHalfSize() const
{
	float Size = 0.f;
	if (BlockType == EBlockType::Hero)
	{
		Size = MOVE_SPACE * 2.f;
	}
	else if (BlockType == EBlockType::Teewee)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::SmashBody)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::LeftRicky)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::RightRicky)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::Cleveland)
	{
		Size = MOVE_SPACE;
	}
	else if (BlockType == EBlockType::RhodeIsland)
	{
		Size = MOVE_SPACE;
	}

	return Size;
}

void ABlock::Move(EBlockDirection _Dir)
{
	FVector Move = FVector::ZeroVector;
	switch (_Dir)
	{
	case EBlockDirection::Up:
		Move = FVector(0.f, 0.f, MOVE_SPACE);	// Temp
		break;
	case EBlockDirection::Down:
		Move = FVector(0.f, 0.f, -MOVE_SPACE);
		break;
	case EBlockDirection::Left:
		Move = FVector(0.f, -MOVE_SPACE, 0.f);
		break;
	case EBlockDirection::Right:
		Move = FVector(0.f, MOVE_SPACE, 0.f);
		break;
	}

	FVector Loc = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), Loc.X, Loc.Y, Loc.Z);

	AddActorLocalOffset(Move);
	//SetActorLocation(Loc + Move, true);
}