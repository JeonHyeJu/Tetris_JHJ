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

	void Move(EBlockDirection _Dir);
	void SetBlockType(EBlockType _Type);

protected:
	virtual void BeginPlay() override;
	
private:
	bool CanMove();

	EBlockType BlockType = EBlockType::Size;

	// TODO: move to static literal
	const float FLOOR_Z_LOW = 125.f;
	const float FLOOR_Z_HIGH = 175.f;
	const float MOVE_SPACE = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh = nullptr;
};
