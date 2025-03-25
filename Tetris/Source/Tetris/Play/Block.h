// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class TETRIS_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlock();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SM", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh = nullptr;
};
