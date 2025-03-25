// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalData.generated.h"


UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Hero UMETA(DisplayName="Hero"),
	Teewee UMETA(DisplayName="Teewee"),
	SmashBody UMETA(DisplayName="SmashBody"),
	LeftRicky UMETA(DisplayName="LeftRicky"),
	RightRicky UMETA(DisplayName="RightRicky"),
	Cleveland UMETA(DisplayName="Cleveland"),
	RhodeIsland UMETA(DisplayName="RhodeIsland"),
};

/**
 * 
 */
UCLASS()
class TETRIS_API UGlobalData : public UObject
{
	GENERATED_BODY()
	
};
