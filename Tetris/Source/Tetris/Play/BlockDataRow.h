// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlockDataRow.generated.h"

USTRUCT(BlueprintType)
struct FBlockDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	TSubclassOf<AActor> BP_BlockClass = nullptr;
};

/**
 * 
 */
UCLASS()
class TETRIS_API UBlockDataRow : public UObject
{
	GENERATED_BODY()
	
};
