// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrameGrid.generated.h"

UCLASS()
class TETRIS_API AFrameGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AFrameGrid();
	virtual void Tick(float DeltaTime) override;

	int GetRows() const;
	int GetCols() const;
	float GetRadius() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", meta = (AllowPrivateAccess = "true"))
	int Rows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", meta = (AllowPrivateAccess = "true"))
	int Cols = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Grid", meta = (AllowPrivateAccess = "true"))
	float Radius = 100.f;
};
