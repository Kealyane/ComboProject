// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Datas/MyEnums.h"
#include "ComboComponent.generated.h"

class AEnemyCharacter;
class UComboAnimInstance;
class AComboProjectCharacter;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AnimationMontage;

	TMap<EInputType, TSharedPtr<FComboNode>> Nodes;
	
	FComboNode(): AttackName(EAttackType::None), Damage(0.f), StaminaCost(0.f), Animation(nullptr), AnimationMontage(nullptr) {}

	FComboNode(EAttackType InAttack, float InDamage, float InStaminaCost, UAnimSequence* InAnimation, UAnimMontage* InAnimationMontage) :
	AttackName(InAttack), Damage(InDamage), StaminaCost(InStaminaCost), Animation(InAnimation), AnimationMontage(InAnimationMontage) {}

	bool IsLastCombo() const { return Nodes.IsEmpty(); }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBOPROJECT_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComboComponent();

	FORCEINLINE bool IsComboActive() const { return bIsComboActive; }
	FORCEINLINE bool IsInputWindowOpen() const { return bInputWindowOpen; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combos", meta=(AllowPrivateAccess="true"))
	//TObjectPtr<UComboNodeAsset> ComboEntryAsset;
	UComboNodeAsset* ComboEntryAsset;
	
	TSharedPtr<FComboNode> ComboGraph;
	
	bool bIsComboActive;
	bool bInputWindowOpen;
	bool bHasReceivedInput;
	bool bIsEnemyInRange;

	virtual void BeginPlay() override;
	
	void InitGraph();
	void StartCombo(EInputType InputName);
	void NextCombo(EInputType InputName);
	void EndCombo();

	/* Bind to Charecter delegates */
	UFUNCTION()
	void OnInputReceived(EInputType InputReceived);
	UFUNCTION()
	void OnSwordHit(bool bIsHitting, AEnemyCharacter* EnemyCharacter);
	
	/* Bind to AnimInstance delegates */
	UFUNCTION()
	void OnInputWindowOpen(bool bIsOpen);
	UFUNCTION()
	void OnApplyEffect();
	UFUNCTION()
	void OnAnimHit();

private:
	TObjectPtr<UComboAnimInstance> AnimInstance;
	TObjectPtr<AComboProjectCharacter> ComboCharacter;
	TSharedPtr<FComboNode> CurrentComboNode;
	TObjectPtr<AEnemyCharacter> EnemyHit;
	
	void InitComboNodes(const TSharedPtr<FComboNode> *CurrentNode, const UComboNodeAsset* CurrentComboAsset);
	void DebugGraph(const TSharedPtr<FComboNode>& Node, const FString& Indent);
};
