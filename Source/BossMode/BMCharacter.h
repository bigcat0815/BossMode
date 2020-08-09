// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "BMProjectile.h"
#include "GameFramework/Character.h"
#include "BMCharacter.generated.h"

UCLASS()
class BOSSMODE_API ABMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPGunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComponent;

public:
	//좌우회전속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	//위아래속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	

	//발사체
public:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<ABMProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = Projectile)
	class USceneComponent* ProjSpawn;

protected:
	void OnFire();

	//추적
protected:
	USceneComponent* TrackingSceneComponent;

	void OnTrack();
	
};
