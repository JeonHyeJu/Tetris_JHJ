// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Block.h"
#include "Engine/HitResult.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	InnerWrapper = CreateDefaultSubobject<USceneComponent>(TEXT("InnerWrapper"));
	InnerWrapper->SetupAttachment(RootComponent);

	/*for (int i = 0; i < 4; ++i)
	{
		UStaticMeshComponent* Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
		Block->SetupAttachment(InnerWrapper);
		BlockMeshes.Add(Block);
	}*/

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	BlockMesh->SetupAttachment(InnerWrapper);
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

TArray<TPair<int, int>> ABlock::GetBlockIndices(int I, int J, int _Degree)
{
	TArray<TPair<int, int>> Idxs;
	Idxs.Reserve(4);

	if (_Degree == 0)
	{
		_Degree = BlockRotation;
	}

	if (BlockType == EBlockType::Hero)
	{
		for (int i = -2; i < 2; ++i)
		{
			if (_Degree == 90 || _Degree == 270)
			{
				Idxs.Add(TPair<int, int>{ I - 1, J + i + 1 });
			}
			else
			{
				Idxs.Add(TPair<int, int>{ I + i, J });
			}
		}
	}
	else if (BlockType == EBlockType::Teewee)
	{
		if (_Degree == 90)
		{
			Idxs.Add(TPair<int, int>{ I - 1, J - 1 });
			Idxs.Add(TPair<int, int>{ I, J - 1 });
			Idxs.Add(TPair<int, int>{ I + 1, J - 1 });
			Idxs.Add(TPair<int, int>{ I, J });
		}
		else if (_Degree == 180)
		{
			Idxs.Add(TPair<int, int>{ I - 1, J });
			Idxs.Add(TPair<int, int>{ I - 1, J - 1 });
			Idxs.Add(TPair<int, int>{ I - 1, J + 1 });
			Idxs.Add(TPair<int, int>{ I, J });
			int a = 0;
		}
		else if (_Degree == 270)
		{
			Idxs.Add(TPair<int, int>{ I - 1, J });
			Idxs.Add(TPair<int, int>{ I, J - 1 });
			Idxs.Add(TPair<int, int>{ I + 1, J });
			Idxs.Add(TPair<int, int>{ I, J });
		}
		else
		{
			Idxs.Add(TPair<int, int>{ I - 1, J });
			Idxs.Add(TPair<int, int>{ I, J });
			Idxs.Add(TPair<int, int>{ I, J - 1 });
			Idxs.Add(TPair<int, int>{ I, J + 1 });
		}
	}
	else if (BlockType == EBlockType::SmashBody)
	{
		Idxs.Add(TPair<int, int>{ I - 1, J });
		Idxs.Add(TPair<int, int>{ I - 1, J + 1 });
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
	}
	else if (BlockType == EBlockType::LeftRicky)
	{
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I, J - 1 });
		Idxs.Add(TPair<int, int>{ I - 1, J - 1 });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
	}
	else if (BlockType == EBlockType::RightRicky)
	{
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
		Idxs.Add(TPair<int, int>{ I - 1, J + 1 });
		Idxs.Add(TPair<int, int>{ I, J - 1 });
	}
	else if (BlockType == EBlockType::Cleveland)
	{
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I - 1, J });
		Idxs.Add(TPair<int, int>{ I - 1, J + 1 });
		Idxs.Add(TPair<int, int>{ I, J - 1 });
	}
	else if (BlockType == EBlockType::RhodeIsland)
	{
		Idxs.Add(TPair<int, int>{ I, J });
		Idxs.Add(TPair<int, int>{ I - 1, J });
		Idxs.Add(TPair<int, int>{ I - 1, J - 1 });
		Idxs.Add(TPair<int, int>{ I, J + 1 });
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

void ABlock::Move(int I, int J, int _Width)
{
	const float SIZE = 100.f;
	FVector Loc(0.f, J * SIZE + _Width, I * SIZE + 200.f);
	SetActorLocation(Loc);
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

void ABlock::Rotate()
{
	if (BlockType == EBlockType::SmashBody)
	{
		return;
	}

	BlockRotation += 90;
	if (BlockRotation == 360)
	{
		BlockRotation = 0;
	}

	InnerWrapper->SetRelativeRotation(FQuat::MakeFromEuler({ StaticCast<float>(BlockRotation), 0.f, 0.f }));

	if (BlockRotation == 0)
	{
		AddActorLocalOffset(FVector{ 0.f, 50.f, 50.f });
	}
	else if (BlockRotation == 90)
	{
		AddActorLocalOffset(FVector{ 0.f, -50.f, -50.f });
	}
	else if (BlockRotation == 180)
	{
		AddActorLocalOffset(FVector{ 0.f, 50.f, 50.f });
	}
	else if (BlockRotation == 270)
	{
		AddActorLocalOffset(FVector{ 0.f, -50.f, 50.f });
	}
}

// Temp
int ABlock::GetFutureDegree() const
{
	int Degree = BlockRotation;
	Degree += 90;
	if (Degree == 360)
	{
		Degree = 0;
	}

	return Degree;
}

void ABlock::SetIndexes(int I, int J)
{
}