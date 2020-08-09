// Fill out your copyright notice in the Description page of Project Settings.


#include "BMAIController.h"
#include "BMBossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ABMAIController::ABMAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	check(BlackboardComp);

	BehaviortreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	check(BehaviortreeComp);

}

const UBlackboardComponent* ABMAIController::GetBlackBoard() const
{
	return BlackboardComp;
}

void ABMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABMBossCharacter* possessedPawn = Cast<ABMBossCharacter>(InPawn);
	if (InPawn != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(possessedPawn->BehaviorTree->BlackboardAsset));
		BehaviortreeComp->StartTree(*(possessedPawn->BehaviorTree));
	}
}
