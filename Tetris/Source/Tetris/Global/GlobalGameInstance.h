// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Global/GlobalData.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	TSubclassOf<AActor> GetBlockClass(EBlockType _Type);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global", meta = (AllowPrivateAccess="true"))
	UDataTable* BlockDataTable = nullptr;
};
