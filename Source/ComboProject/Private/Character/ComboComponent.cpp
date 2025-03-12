// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ComboComponent.h"
#include "ComboProject/ComboProjectCharacter.h"
#include "Datas/ComboNodeAsset.h"

UComboComponent::UComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsComboActive = false;
	bInputWindowOpen = false;
	bIsBeforeInputWindow = false;
}

void UComboComponent::BeginPlay()
{
	Super::BeginPlay();

	ComboCharacter = Cast<AComboProjectCharacter>(GetOwner());
	SkeletalMesh = ComboCharacter->GetMesh();
	InitGraph();

	ComboCharacter->InputFired.BindUFunction(this, FName("OnInputReceived"));
	// Debug
	DebugGraph(ComboGraph, TEXT(""));
}

void UComboComponent::StartCombo(EInputType InputName)
{
	bIsComboActive = true;
	bInputWindowOpen = false;
	bIsBeforeInputWindow = true;

	CurrentComboNode = (*ComboGraph).Nodes[InputName];
	if (SkeletalMesh)
	{
		SkeletalMesh->PlayAnimation(CurrentComboNode->Animation, false);
	}
}

void UComboComponent::NextCombo(EInputType InputName)
{
	CurrentComboNode = (*CurrentComboNode).Nodes[InputName];
	if (SkeletalMesh)
	{
		SkeletalMesh->PlayAnimation(CurrentComboNode->Animation, false);
	}
}

void UComboComponent::EndCombo()
{
	bIsComboActive = false;
	bInputWindowOpen = false;
	bIsBeforeInputWindow = false;
}

void UComboComponent::OnInputReceived(EInputType InputReceived)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Input Received"));
}

void UComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UComboComponent::InitGraph()
{
	if (ComboEntryAsset == nullptr)
	{
		return;
	}

	ComboGraph = MakeShared<FComboNode>();
	for (TObjectPtr<UComboNodeAsset> ComboAsset : ComboEntryAsset->NextCombos)
	{
		TSharedPtr<FComboNode> NewNode = MakeShared<FComboNode>(
			ComboAsset->AttackStatsAsset->AttackName,
			ComboAsset->AttackStatsAsset->Damage,
			ComboAsset->AttackStatsAsset->StaminaCost,
			ComboAsset->AttackStatsAsset->Animation);
		
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
			ComboAsset->AttackStatsAsset->Animation);
		
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

