// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Hit.h"

#include "Animation/ComboAnimInstance.h"

void UAnimNotify_Hit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Notify : Hit"));

	UComboAnimInstance* AnimInstance = Cast<UComboAnimInstance>(MeshComp->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->AnimHit.Broadcast();
	}
}
