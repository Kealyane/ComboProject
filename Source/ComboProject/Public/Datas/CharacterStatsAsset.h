// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterStatsAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class COMBOPROJECT_API UCharacterStatsAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Health = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Stamina = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float StaminaRegenRate = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float StaminaDelayBeforeRegen = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float BaseAttack = 5.f;
	
};
