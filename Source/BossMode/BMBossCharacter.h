// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "GameFramework/Character.h"
#include "BMBossCharacter.generated.h"

UCLASS()
class BOSSMODE_API ABMBossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABMBossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = AI)
	float GetHealth() const;

	UPROPERTY(EditAnywhere, Category = Pawn)
	class UBehaviorTree* BehaviorTree;

private:

	UPROPERTY()
	float Health;

};
