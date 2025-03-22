// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"


class UCharacterStatsAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBOPROJECT_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatsComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCharacterStatsAsset> CharacterStatsAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Health", meta=(AllowPrivateAccess=true))
	float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Health", meta=(AllowPrivateAccess=true))
	float CurrentHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Stamina", meta=(AllowPrivateAccess=true))
	float MaxStamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Stamina", meta=(AllowPrivateAccess=true))
	float CurrentStamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Stamina", meta=(AllowPrivateAccess=true))
	float StaminaRegenRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Stamina", meta=(AllowPrivateAccess=true))
	float StaminaDelayBeforeRegen;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Attack", meta=(AllowPrivateAccess=true))
	float BaseAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats|Attack", meta=(AllowPrivateAccess=true))
	float CurrentAttack;

	virtual void BeginPlay() override;

	UFUNCTION()
	void InitStats();
	UFUNCTION()
	void RegenerateStamina();

public:	

	UFUNCTION()
	void ChangeHP(float Value);
	UFUNCTION()
	void ChangeStamina(float Value);
	UFUNCTION()
	bool HasStamina(float Value);

	UFUNCTION()
	float GetCurrentHP() const { return CurrentHP; }
	UFUNCTION()
	float GetMaxHP() const { return MaxHP; }
	UFUNCTION()
	float GetBaseAttack() const { return BaseAttack; }

private:
	FTimerHandle StaminaTimerHandle;
};
