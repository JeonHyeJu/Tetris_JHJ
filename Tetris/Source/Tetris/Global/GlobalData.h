// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalData.generated.h"

USTRUCT()
struct FInitData
{
	GENERATED_BODY()

	int Rows = 0;
	int Cols = 0;
	float Radius = 0.f;
};

UENUM()
enum class EBlockDirection : int8
{
	None = -1,
	Up,
	Down,
	Left,
	Right,
};

UENUM()
enum class EBlockType : uint8
{
	Hero,
	Teewee,
	SmashBody,
	LeftRicky,
	RightRicky,
	Cleveland,
	RhodeIsland,
	Size,
	OutBlock,
};

/**
 * 
 */
UCLASS()
class TETRIS_API UGlobalData : public UObject
{
	GENERATED_BODY()
	
};
