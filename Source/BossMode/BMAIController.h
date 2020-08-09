// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "AIController.h"
#include "BMAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSMODE_API ABMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABMAIController();

	//const UBlackboardComponent* GetBlackBoard() const;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	//UPROPERTY(BlueprintReadWrite, Category = Behavior)
	//class UBlackboardComponent* BlackboardComp;

	//UPROPERTY(BlueprintReadWrite, Category = Behavior)
	//class UBehaviorTreeComponent* BehaviortreeComp;


	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBlackboardData* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBehaviorTree* BehaviortreeComp;

public:
	static const FName HomePosKey;
	static const FName TargetPosKey;
//	static const FName TargetKey;

//private:
//	void OnRepeatTimer();
//
//	FTimerHandle RepeatimerHandle;
//	float RepeatInterval;


};
