// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/EnemyWidget.h"

#include "Components/ProgressBar.h"

void UEnemyWidget::SetHealthBar(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

void UEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetHealthBar(1.f);
}
