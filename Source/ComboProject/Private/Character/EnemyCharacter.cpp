// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "Character/CharacterStatsComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/EnemyWidget.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("StatsComponent"));

	// DO NOT WORK, WIDGET NOT VISIBLE
	// WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	// WidgetComponent->SetupAttachment(RootComponent);
	// WidgetComponent->SetVisibility(true);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsHit = false;
	check(StatsComponent);
}

void AEnemyCharacter::UpdateHealth(float AttackValue)
{
	StatsComponent->ChangeHP(-AttackValue);
	EnemyWidget->SetHealthBar(StatsComponent->GetCurrentHP()/StatsComponent->GetMaxHP());
	bIsHit = true;

	FTimerHandle ResetHitHandle;
	GetWorldTimerManager().SetTimer(ResetHitHandle, this, &AEnemyCharacter::ResetHit, 1.f, false);
}

void AEnemyCharacter::SetWidgetComponent(UWidgetComponent* InWidgetComponent)
{
	WidgetComponent = InWidgetComponent; 
	EnemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetWidget());
	check(EnemyWidget);
}


// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

