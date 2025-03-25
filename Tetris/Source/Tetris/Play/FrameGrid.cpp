// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/FrameGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalGameInstance.h"

AFrameGrid::AFrameGrid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFrameGrid::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() == nullptr)
	{
		return;
	}

	UGlobalGameInstance* GameInst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInst == nullptr)
	{
		return;
	}

	FInitData Data{ Rows, Cols, Radius };
	GameInst->SetInitData(Data);
}

void AFrameGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AFrameGrid::GetRows() const
{
	return Rows;
}

int AFrameGrid::GetCols() const
{
	return Cols;
}

float AFrameGrid::GetRadius() const
{
	return Radius;
}
