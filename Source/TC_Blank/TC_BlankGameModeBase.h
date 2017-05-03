// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "TC_BlankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TC_BLANK_API ATC_BlankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

    void OnGolfBallPhsics(float fDeltaTime, FBodyInstance* biTargetBody);
	
	
};
