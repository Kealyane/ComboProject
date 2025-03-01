// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnums.h"
#include "Engine/DataAsset.h"
#include "AttackStatsAsset.generated.h"

/**
 * 
 */
UCLASS()
class COMBOPROJECT_API UAttackStatsAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	EAttackType AttackName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	TObjectPtr<UAnimSequence> Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float StaminaCost;
};
