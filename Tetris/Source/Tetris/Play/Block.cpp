// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Block.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	BlockMesh->SetupAttachment(RootComponent);
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

