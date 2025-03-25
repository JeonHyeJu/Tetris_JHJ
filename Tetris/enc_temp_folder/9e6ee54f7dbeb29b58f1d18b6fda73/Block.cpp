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

void ABlock::SetBlockType(EBlockType _Type)
{
	BlockType = _Type;
}

bool ABlock::CanMove()
{
	bool IsMove = false;

	if (BlockType == EBlockType::Hero)
	{

	}
	else if (BlockType == EBlockType::Teewee)
	{

	}
	else if (BlockType == EBlockType::SmashBody)
	{

	}
	else if (BlockType == EBlockType::LeftRicky)
	{

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

	return IsMove;
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