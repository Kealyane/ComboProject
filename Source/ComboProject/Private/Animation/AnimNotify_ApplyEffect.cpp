// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ApplyEffect.h"

#include "Animation/ComboAnimInstance.h"

void UAnimNotify_ApplyEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UComboAnimInstance* AnimInstance = Cast<UComboAnimInstance>(MeshComp->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->AnimApplyEffect.Broadcast();
	}
}
