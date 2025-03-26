// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/GlobalData.h"
#include "Block.generated.h"

UCLASS()
class TETRIS_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlock();
	virtual void Tick(float DeltaTime) override;

	void Move(int I, int J, int _Width);	// Width Temp
	void Move(EBlockDirection _Dir);
	void Rotate();
	int GetFutureDegree() const;
	void SetBlockType(EBlockType _Type);
	EBlockType GetBlockType() const;
	TArray<TPair<int, int>> GetBlockIndices(int I, int J, int _Degree=0);
	void SetIndexes(int I, int J);

	// Temp
	int X = 0;
	int Y = 0;

	FVector InitialLoc = FVector::ZeroVector;

protected:
	virtual void BeginPlay() override;
	
private:
	EBlockType BlockType = EBlockType::Size;

	// TODO: move to static literal
	const float FLOOR_Z_LOW = 125.f;
	const float FLOOR_Z_HIGH = 175.f;
	const float MOVE_SPACE = 100.f;
	int BlockRotation = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InnerWrapper = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh = nullptr;

	TArray<TPair<int, int>> Indexes;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> BlockMeshes;*/
};
