// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "BehaviorTree/BTService.h"
#include "BM_BTS_ArgoCheck.generated.h"

/**
 * 
 */
UCLASS()
class BOSSMODE_API UBM_BTS_ArgoCheck : public UBTService
{
	GENERATED_BODY()
	
public:
	UBM_BTS_ArgoCheck();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UBehaviorTree* ThisTree;
	class ABMAIController* ThisController;
	class ABMBossCharacter* ThisAICharacter;

};
