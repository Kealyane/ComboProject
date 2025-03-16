// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComboNodeAsset.h"
#include "Engine/DataAsset.h"
#include "ComboGraphAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class COMBOPROJECT_API UComboGraphAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Graph Asset")
	TArray<TObjectPtr<UComboNodeAsset>> ComboGraph;
};
