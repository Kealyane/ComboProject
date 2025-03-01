// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnums.generated.h"


UENUM(BlueprintType)
enum class EAttackType : uint8
{
    LightAttackA    UMETA(DisplayName = "LightAttackA"),
    LightAttackB    UMETA(DisplayName = "LightAttackB"),
    HeavyAttackA    UMETA(DisplayName = "HeavyAttackA"),
    HeavyAttackB    UMETA(DisplayName = "HeavyAttackB"),
};

UENUM(BlueprintType)
enum class EInputType : uint8
{
    None        UMETA(DisplayName = "None"),
    MouseLeft   UMETA(DisplayName = "MouseLeft"),
    MouseRight  UMETA(DisplayName = "MouseRight"),
};

namespace EnumDebugHelper
{
    static FString AttackToString(EAttackType EnumValue)
    {
        switch (EnumValue)
        {
        case EAttackType::LightAttackA: return TEXT("Light Attack A");
        case EAttackType::LightAttackB: return TEXT("Light Attack B");
        case EAttackType::HeavyAttackA: return TEXT("Heavy Attack A");
        case EAttackType::HeavyAttackB: return TEXT("Heavy Attack B");
        default: return TEXT("NONE");
        }
    }
    static FString InputToString(EInputType EnumValue)
    {
        switch (EnumValue)
        {
        case EInputType::None: return TEXT("No input");
        case EInputType::MouseLeft: return TEXT("Mouse Left");
        case EInputType::MouseRight: return TEXT("Mouse Right");
        default: return TEXT("NONE");
        }
    }
}