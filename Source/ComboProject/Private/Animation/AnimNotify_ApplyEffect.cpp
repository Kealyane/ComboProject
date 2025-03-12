// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ApplyEffect.h"

void UAnimNotify_ApplyEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Notify ApplyEffect"));
}
