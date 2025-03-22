// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UEnemyWidget;
class UWidgetComponent;
class UCharacterStatsComponent;
class UCharacterStatsAsset;

UCLASS()
class COMBOPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(BlueprintCallable)
	UCharacterStatsComponent* GetCharacterStatsComponent() const { return StatsComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHit;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatsComponent> StatsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ResetHit() { bIsHit = false; }

public:	

	UFUNCTION()
	void UpdateHealth(float AttackValue);

	UFUNCTION(BlueprintCallable)
	void SetWidgetComponent(UWidgetComponent* InWidgetComponent);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	TObjectPtr<UEnemyWidget> EnemyWidget;

};
