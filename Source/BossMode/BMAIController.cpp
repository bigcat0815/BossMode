// Fill out your copyright notice in the Description page of Project Settings.


#include "BMAIController.h"
#include "BMBossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName ABMAIController::HomePosKey(TEXT("HomePos"));
const FName ABMAIController::TargetPosKey(TEXT("PatrolPos"));
const FName ABMAIController::TargetKey(TEXT("Target"));

ABMAIController::ABMAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
		TEXT("/Game/BB/BB_BossMode2.BB_BossMode2"));
	if (BBObject.Succeeded())
	{
		BlackboardComp =  BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
		TEXT("/Game/BB/BT_BossMode2.BT_BossMode2"));
	if (BTObject.Succeeded())
	{
		BehaviortreeComp = BTObject.Object;
	}

	//EBossState::BS_FOLLOW;

	//BBcomp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBoardComp"));
	//check(BBcomp);

	//BehaviortreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	//check(BehaviortreeComp);

}

//const UBlackboardComponent* ABMAIController::GetBlackBoard() const
//{
//	return BlackboardComp;
//}

void ABMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardComp, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		
		//BossStateBlackboardKey = BBcomp->GetKeyID("BossState");
		if (!RunBehaviorTree(BehaviortreeComp))
		{
			UE_LOG(BossMode,Error, TEXT("AIController, can't run Behavior Tree!"));
		}
	}



	/*ABMBossCharacter* possessedPawn = Cast<ABMBossCharacter>(InPawn);
	if (InPawn != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(possessedPawn->BehaviorTree->BlackboardAsset));
		BehaviortreeComp->StartTree(*(possessedPawn->BehaviorTree));
	}*/
}

void ABMAIController::Tick(float DeltaTime)
{
	//EBossState bossState;
	//if (ControlledChar->GetHealth() > 66.0f)
	//{
	//	bossState = EBossState::BS_FOLLOW;
	//}
	//else if(ControlledChar->GetHealth() > 33.0f)
	//{
	//	bossState = EBossState::BS_TURRET;
	//}
	//else
	//{
	//	bossState = EBossState::BS_FINAL;
	//}
	//BBcomp->SetValue<UBlackboardKeyType_Enum>(BossStateBlackboardKey, (uint8)bossState);
}

//void ABMAIController::OnRepeatTimer()
//{
//}
