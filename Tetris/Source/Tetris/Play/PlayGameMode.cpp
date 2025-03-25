// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/PlayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalGameInstance.h"

void APlayGameMode::BeginPlay()
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

	TSubclassOf<AActor> ActorClass = GameInst->GetBlockClass(EBlockType::Teewee);
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass);
	SpawnedActor->SetActorLocation(FVector(100.f, 0.f, 200.f));

	Blocks.Add(SpawnedActor);
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 하나만 존재
	static float ElapsedSecs = 0.f;

	ElapsedSecs += _DeltaTime;
	if (ElapsedSecs >= GEN_SEC)
	{
		ElapsedSecs = 0.f;
		GenerateBlock();
	}
}

void APlayGameMode::GenerateBlock()
{
	static const int Min = 0;
	static const int Max = 6;

	int Value = FMath::RandRange(Min, Max);

	UE_LOG(LogTemp, Log, TEXT("value: %d"), Value);
}