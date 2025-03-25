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

	const FInitData& GetInitData() const;
	void SetInitData(const FInitData& _Data);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global", meta = (AllowPrivateAccess="true"))
	UDataTable* BlockDataTable = nullptr;

	FInitData InitData;
};
