// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "GameFramework/Actor.h"
#include "BMProjectile.generated.h"

UCLASS()
class BOSSMODE_API ABMProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* ProjeCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* ProjParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ProjMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* ProjMovement;

public:
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnDestoyedProjectile(AActor* DestoyingActor);
};
