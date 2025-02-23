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
	TSoftObjectPtr<UCharacterStatsAsset> CharacterStatsAsset;
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

public:	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ChangeHP(float Value);
	UFUNCTION()
	void ChangeStamina(float Value);
	UFUNCTION()
	void RegenerateStamina();

private:
	FTimerHandle StaminaTimerHandle;
};
