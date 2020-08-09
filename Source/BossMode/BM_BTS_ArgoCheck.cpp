// Fill out your copyright notice in the Description page of Project Settings.


#include "BM_BTS_ArgoCheck.h"
#include "BMAIController.h"
#include "BMBossCharacter.h"
#include "BMCharacter.h"
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

	TArray<FOverlapResult> OverlapResults;

	

	bool bResult = ThisAICharacter->GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		//ThisAICharacter->GetActorLocation(), 
		ThisAICharacter->GetActorLocation() + FVector(0.f, 0.f, 10.f),
		FQuat(), 
		//ObjectQuery,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(1500), 
		SphereSweepParams);


	//Target¿˙¿Â
	if (bResult)
	{
		for (auto overlapResult : OverlapResults)
		{
			//FName bmTags(TEXT("bigcat")); 
			ABMCharacter* MainCharacter = Cast<ABMCharacter>(overlapResult.GetActor());

			if (MainCharacter && MainCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABMAIController::TargetKey, MainCharacter);
				DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Green, false, 2.0f);
				UE_LOG(BossMode, Warning, TEXT("Target Success!!"));
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABMAIController::TargetKey, nullptr);
	}
	DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Red, false, 4.0f);
	//if (bResult)
	//{
	//	ThisController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetToFollow"),HitOut.GetActor());
	//	ThisController->GetBlackboardComponent()->SetValueAsVector(TEXT("HomeLocation"),ThisAICharacter->GetActorLocation());
	//	ThisController->GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"),HitOut.GetActor()->GetActorLocation());
	//}
	//else
	//{
	//	ThisController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetToFollow"), nullptr);
	//	
	//}

}
