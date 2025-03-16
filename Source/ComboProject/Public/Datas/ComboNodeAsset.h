// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackStatsAsset.h"
#include "Engine/DataAsset.h"
#include "ComboNodeAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class COMBOPROJECT_API UComboNodeAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	EInputType InputName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	TObjectPtr<UAttackStatsAsset> AttackStatsAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	TArray<TObjectPtr<UComboNodeAsset>> NextCombos;
};
