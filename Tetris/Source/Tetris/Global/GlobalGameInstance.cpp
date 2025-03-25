// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalGameInstance.h"
#include "Play/BlockDataRow.h"

TSubclassOf<AActor> UGlobalGameInstance::GetBlockClass(EBlockType _Type)
{
	UE_LOG(LogTemp, Error, TEXT("Data table is nullptr"));
	if (BlockDataTable == nullptr)
	{
		return nullptr;
	}

	FName Name = "";
	switch (_Type)
	{
	case EBlockType::Hero:
		Name = TEXT("Hero");
		break;
	case EBlockType::Teewee:
		Name = TEXT("Teewee");
		break;
	case EBlockType::SmashBody:
		Name = TEXT("SmashBody");
		break;
	case EBlockType::LeftRicky:
		Name = TEXT("LeftRicky");
		break;
	case EBlockType::RightRicky:
		Name = TEXT("RightRicky");
		break;
	case EBlockType::Cleveland:
		Name = TEXT("Cleveland");
		break;
	case EBlockType::RhodeIsland:
		Name = TEXT("RhodeIsland");
		break;
	}

	FBlockDataTableRow* Row = BlockDataTable->FindRow<FBlockDataTableRow>(Name, nullptr);
	if (Row)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Class: %s"), *Row->BP_BlockClass->GetName());

		return Row->BP_BlockClass;
	}

	return nullptr;
}