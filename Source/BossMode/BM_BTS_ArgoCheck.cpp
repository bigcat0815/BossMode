// Fill out your copyright notice in the Description page of Project Settings.


#include "BM_BTS_ArgoCheck.h"
#include "BMAIController.h"
#include "BMBossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DrawDebugHelpers.h"

UBM_BTS_ArgoCheck::UBM_BTS_ArgoCheck()
{
	NodeName = TEXT("ArgoCheck");
}

void UBM_BTS_ArgoCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr)
	{
		ThisTree = OwnerComp.GetCurrentTree();
		ThisController = Cast<ABMAIController>(OwnerComp.GetAIOwner());
		ThisAICharacter = Cast<ABMBossCharacter>(ThisController->GetPawn());

		if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr)
		{
			UE_LOG(BossMode, Warning, TEXT("Argo Service Error"));
			return;
		}
	}

	FCollisionQueryParams SphereSweepParams(FName(TEXT("AgroCheckSweep")), true, ThisAICharacter);
	FCollisionObjectQueryParams ObjectQuery(ECC_GameTraceChannel2);
	FHitResult HitOut(ForceInit);

	DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Red, false, 4.0f);

	bool bResult = ThisAICharacter->GetWorld()->SweepSingleByObjectType(
		HitOut,
		ThisAICharacter->GetActorLocation(), 
		ThisAICharacter->GetActorLocation() + FVector(0.f, 0.f, 10.f),
		FQuat(), 
		ObjectQuery,
		FCollisionShape::MakeSphere(1500), 
		SphereSweepParams);

	if (bResult)
	{
		ThisController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetToFollow"),HitOut.GetActor());
		ThisController->GetBlackboardComponent()->SetValueAsVector(TEXT("HomeLocation"),ThisAICharacter->GetActorLocation());
		ThisController->GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"),HitOut.GetActor()->GetActorLocation());
	}
	else
	{
		ThisController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetToFollow"), nullptr);
		
	}

}
