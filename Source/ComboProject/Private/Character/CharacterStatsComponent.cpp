// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterStatsComponent.h"

#include "Datas/CharacterStatsAsset.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	InitStats();
}

void UCharacterStatsComponent::InitStats()
{
	if (CharacterStatsAsset)
	{
		MaxHP = CharacterStatsAsset->Health;
		CurrentHP = MaxHP;

		MaxStamina = CharacterStatsAsset->Stamina;
		CurrentStamina = MaxStamina;
		StaminaRegenRate = CharacterStatsAsset->StaminaRegenRate;
		StaminaDelayBeforeRegen = CharacterStatsAsset->StaminaDelayBeforeRegen;
		
		BaseAttack = CharacterStatsAsset->BaseAttack;
		CurrentAttack = BaseAttack;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterStatsAsset is NULL"));
	}
}

void UCharacterStatsComponent::ChangeHP(float Value)
{
	CurrentHP = FMath::Clamp(CurrentHP + Value, 0.f, MaxHP);
}

void UCharacterStatsComponent::ChangeStamina(float Value)
{
	GetWorld()->GetTimerManager().ClearTimer(StaminaTimerHandle);
	
	CurrentStamina = FMath::Clamp(CurrentStamina + Value, 0.f, MaxStamina);

	if (CurrentStamina < MaxStamina)
	{
		GetWorld()->GetTimerManager().SetTimer(
			StaminaTimerHandle,
			this,
			&UCharacterStatsComponent::RegenerateStamina,
			StaminaRegenRate,
			true,
			StaminaDelayBeforeRegen);
	}
}

void UCharacterStatsComponent::RegenerateStamina()
{
	if (CurrentStamina >= MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaTimerHandle);
		CurrentStamina = MaxStamina;
		return;
	}
	CurrentStamina += 1.f;
}

bool UCharacterStatsComponent::HasStamina(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan,
		FString::Printf(TEXT("has stamina : %f"), CurrentStamina - Value));
	return CurrentStamina - Value >= 0.f;
}


// // Called every frame
// void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

