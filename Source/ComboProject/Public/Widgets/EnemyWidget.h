// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class COMBOPROJECT_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UFUNCTION()
	void SetHealthBar(float HealthPercent);

protected:
	virtual void NativeConstruct() override;
	
};
