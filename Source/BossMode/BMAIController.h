// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BMAIController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBossState : uint8
{
	BS_FOLLOW = 0 UMETA(DisplayName = "Follow"),
	BS_TURRET = 1 UMETA(DisplayName = "Turret"),
	BS_FINAL = 2 UMETA(DisplayName = "Final")
};

UCLASS()
class BOSSMODE_API ABMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABMAIController();

	//const UBlackboardComponent* GetBlackBoard() const;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

protected:
	//UPROPERTY(BlueprintReadWrite, Category = Behavior)
	//class UBlackboardComponent* BlackboardComp;

	//UPROPERTY(BlueprintReadWrite, Category = Behavior)
	//class UBehaviorTreeComponent* BehaviortreeComp;

	/*UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBlackboardComponent* BBcomp;*/

	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBlackboardData* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBehaviorTree* BehaviortreeComp;

public:
	static const FName HomePosKey;
	static const FName TargetPosKey;
	static const FName TargetKey;


private:
	class ABMBossCharacter* ControlledChar;
	FBlackboard::FKey BossStateBlackboardKey;

//private:
//	void OnRepeatTimer();
//
//	FTimerHandle RepeatimerHandle;
//	float RepeatInterval;


};
