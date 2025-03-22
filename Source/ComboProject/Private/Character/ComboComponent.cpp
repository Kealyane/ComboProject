// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ComboComponent.h"

#include "Animation/ComboAnimInstance.h"
#include "Character/CharacterStatsComponent.h"
#include "Character/EnemyCharacter.h"
#include "ComboProject/ComboProjectCharacter.h"
#include "Datas/ComboNodeAsset.h"

UComboComponent::UComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsComboActive = false;
	bInputWindowOpen = false;
	bHasReceivedInput = false;
	CurrentComboNode = nullptr;
}

void UComboComponent::BeginPlay()
{
	Super::BeginPlay();

	ComboCharacter = Cast<AComboProjectCharacter>(GetOwner());
	check(ComboCharacter);
	
	SkeletalMesh = ComboCharacter->GetMesh();
	check(SkeletalMesh);
	
	AnimInstance = Cast<UComboAnimInstance>(SkeletalMesh->GetAnimInstance());
	check(AnimInstance);

	AnimInstance->AnimInputWindow.AddDynamic(this, &UComboComponent::OnInputWindowOpen);
	AnimInstance->AnimApplyEffect.AddDynamic(this, &UComboComponent::OnApplyEffect);
	AnimInstance->AnimHit.AddDynamic(this, &UComboComponent::OnAnimHit);
	
	InitGraph();

	ComboCharacter->InputFired.BindUFunction(this, FName("OnInputReceived"));
	ComboCharacter->SwordHit.BindUFunction(this, FName("OnSwordHit"));

	// Debug
	DebugGraph(ComboGraph, TEXT(""));
}

void UComboComponent::StartCombo(EInputType InputName)
{
	bIsComboActive = true;
	bInputWindowOpen = false;
	bHasReceivedInput = false;

	if ((*ComboGraph).Nodes.Contains(InputName))
	{
		CurrentComboNode = (*ComboGraph).Nodes[InputName];
		if (ComboCharacter->GetStatsComponent()->HasStamina(CurrentComboNode->StaminaCost))
		{
			AnimInstance->Montage_Play(CurrentComboNode->AnimationMontage);
		}
		else EndCombo();
	}
}

void UComboComponent::NextCombo(EInputType InputName)
{
	if (bInputWindowOpen)
	{
		if ((*CurrentComboNode).Nodes.Contains(InputName))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Next combo: update current"));
			CurrentComboNode = (*CurrentComboNode).Nodes[InputName];
		
			if (ComboCharacter->GetStatsComponent()->HasStamina(CurrentComboNode->StaminaCost))
				bHasReceivedInput = true;
			else
				EndCombo();
		}
		else if (CurrentComboNode->IsLastCombo())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Next combo: Last combo start new combo"));
			EndCombo();
			StartCombo(InputName);
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Next combo : wrong input"));
		bIsComboActive = false;
		CurrentComboNode = nullptr;
		bHasReceivedInput = false;
	}
}

void UComboComponent::EndCombo()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("End Combo"));
	bIsComboActive = false;
	bInputWindowOpen = false;
	bHasReceivedInput = false;
}

void UComboComponent::OnInputReceived(EInputType InputReceived)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan,
	// 	*FString::Printf(TEXT("Input Received %s"), *EnumDebugHelper::InputToString(InputReceived)));
	if (!bIsComboActive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Input Received: combo not active"));
		//if (!AnimInstance->Montage_IsPlaying(nullptr))
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Input Received  : start combo"));
			StartCombo(InputReceived);
		//}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Input Received: combo active"));
		NextCombo(InputReceived);
	}
}

void UComboComponent::OnInputWindowOpen(bool bIsOpen)
{
	if (bIsOpen)
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("OnInputWindowOpen : OPEN"));
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("OnInputWindowOpen : CLOSE"));
	
	bInputWindowOpen = bIsOpen;

	if (!bInputWindowOpen)
	{
		if (!bHasReceivedInput)
		{
			EndCombo();
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("OnInputWindowOpen : close play next anim"));
			AnimInstance->Montage_Play(CurrentComboNode->AnimationMontage);
			bHasReceivedInput = false;
		}
	}
}

void UComboComponent::OnApplyEffect()
{
	if (CurrentComboNode)
	{
		ComboCharacter->GetStatsComponent()->ChangeStamina(-CurrentComboNode->StaminaCost);
	}
}

void UComboComponent::OnAnimHit()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("OnAnimHit"));
	if (bIsEnemyInRange && EnemyHit && CurrentComboNode)
	{
		EnemyHit->UpdateHealth(CurrentComboNode->Damage);
	}
}

void UComboComponent::OnSwordHit(bool bIsHitting, AEnemyCharacter* EnemyCharacter)
{
	// if (bIsHitting)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("OnSwordHit Start"));
	// else
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("OnSwordHit End"));
	bIsEnemyInRange = bIsHitting;
	EnemyHit = EnemyCharacter;
}

void UComboComponent::InitGraph()
{
	if (ComboEntryAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UComboComponent::InitGraph: ComboEntryAsset null"));
		return;
	}

	ComboGraph = MakeShared<FComboNode>();
	for (TObjectPtr<UComboNodeAsset> ComboAsset : ComboEntryAsset->NextCombos)
	{
		TSharedPtr<FComboNode> NewNode = MakeShared<FComboNode>(
			ComboAsset->AttackStatsAsset->AttackName,
			ComboAsset->AttackStatsAsset->Damage,
			ComboAsset->AttackStatsAsset->StaminaCost,
			ComboAsset->AttackStatsAsset->Animation,
			ComboAsset->AttackStatsAsset->AnimationMontage);
		
		ComboGraph->Nodes.Add(ComboAsset->InputName, NewNode);

		InitComboNodes(&NewNode, ComboAsset);
	}
}

void UComboComponent::InitComboNodes(const TSharedPtr<FComboNode> *CurrentNode, const UComboNodeAsset* CurrentComboAsset)
{
	if (CurrentComboAsset->NextCombos.Num() == 0)
	{
		return;
	}

	for (TObjectPtr<UComboNodeAsset> ComboAsset : CurrentComboAsset->NextCombos)
	{
		TSharedPtr<FComboNode> NewNode = MakeShared<FComboNode>(
			ComboAsset->AttackStatsAsset->AttackName,
			ComboAsset->AttackStatsAsset->Damage,
			ComboAsset->AttackStatsAsset->StaminaCost,
			ComboAsset->AttackStatsAsset->Animation,
			ComboAsset->AttackStatsAsset->AnimationMontage);
		
		(*CurrentNode)->Nodes.Add(ComboAsset->InputName, NewNode);

		InitComboNodes(&NewNode, ComboAsset);
	}
}

void UComboComponent::DebugGraph(const TSharedPtr<FComboNode>& Node, const FString& Indent)
{
	if (!Node) return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s[Attack: %s]"), *Indent, *EnumDebugHelper::AttackToString(Node->AttackName));

	for (const auto& Entry : Node->Nodes)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s  |-- Input: %s"), *Indent, *EnumDebugHelper::InputToString(Entry.Key));
		
		DebugGraph(Entry.Value, Indent + TEXT("    "));
	}
}

