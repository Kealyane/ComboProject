// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Datas/MyEnums.h"
#include "ComboComponent.generated.h"

class UComboNodeAsset;

USTRUCT(BlueprintType)
struct FComboNode
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAttackType AttackName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StaminaCost;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> Animation;

	TMap<EInputType, TSharedPtr<FComboNode>> Nodes;
	
	FComboNode(): AttackName(EAttackType::None), Damage(0.f), StaminaCost(0.f), Animation(nullptr) {}

	FComboNode(EAttackType InAttack, float InDamage, float InStaminaCost, UAnimSequence* InAnimation) :
	AttackName(InAttack), Damage(InDamage), StaminaCost(InStaminaCost), Animation(InAnimation) {}

	bool IsLastCombo() const { return Nodes.IsEmpty(); }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBOPROJECT_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComboComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combos")
	TObjectPtr<UComboNodeAsset> ComboEntryAsset;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitGraph();

	
	TSharedPtr<FComboNode> ComboGraph;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	void InitComboNodes(const TSharedPtr<FComboNode> *CurrentNode, const UComboNodeAsset* CurrentComboAsset);
	void DebugGraph(const TSharedPtr<FComboNode>& Node, const FString& Indent);
};
