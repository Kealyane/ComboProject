// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ComboComponent.h"

#include "Datas/ComboNodeAsset.h"

UComboComponent::UComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UComboComponent::BeginPlay()
{
	Super::BeginPlay();

	InitGraph();
	DebugGraph(ComboGraph, TEXT(""));
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

