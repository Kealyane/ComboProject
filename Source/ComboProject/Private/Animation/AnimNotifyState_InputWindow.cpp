// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_InputWindow.h"

#include "Animation/ComboAnimInstance.h"


void UAnimNotifyState_InputWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UComboAnimInstance* AnimInstance = Cast<UComboAnimInstance>(MeshComp->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->AnimInputWindow.Broadcast(true);
	}
}

void UAnimNotifyState_InputWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UComboAnimInstance* AnimInstance = Cast<UComboAnimInstance>(MeshComp->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->AnimInputWindow.Broadcast(false);
	}
}
