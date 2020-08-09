// Fill out your copyright notice in the Description page of Project Settings.


#include "BMBossCharacter.h"

// Sets default values
ABMBossCharacter::ABMBossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.f;

	GetMovementComponent()->NavAgentProps.AgentHeight = 320.f;
	GetMovementComponent()->NavAgentProps.AgentRadius = 160.f;
}

// Called when the game starts or when spawned
void ABMBossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABMBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABMBossCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Health -= Damage;
	return Damage;
}

const float ABMBossCharacter::GetHealth() const
{
	return Health;
}

