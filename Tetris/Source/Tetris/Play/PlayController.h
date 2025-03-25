// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayController.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API APlayController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddInputMappingContext(UInputMappingContext* _Context);
};
