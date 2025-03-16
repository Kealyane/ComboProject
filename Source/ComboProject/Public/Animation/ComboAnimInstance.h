// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ComboAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimApplyEffectSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimHitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimInputWindow, bool, bIsOpen);

/**
 * 
 */
UCLASS()
class COMBOPROJECT_API UComboAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAnimApplyEffectSignature AnimApplyEffect;
	UPROPERTY(BlueprintAssignable)
	FAnimHitSignature AnimHit;
	UPROPERTY(BlueprintAssignable)
	FAnimInputWindow AnimInputWindow;
};
