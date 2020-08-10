// Fill out your copyright notice in the Description page of Project Settings.


#include "BMProjectile.h"
//#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BMBossCharacter.h"
#include "GameFramework/DamageType.h"

// Sets default values
ABMProjectile::ABMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// �߻�ü�� �ݸ��� ó��
	ProjeCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	ProjeCollision->InitSphereRadius(10.f);
	ProjeCollision->BodyInstance.SetCollisionProfileName("BlockAll");	
	ProjeCollision->OnComponentHit.AddDynamic(this, &ABMProjectile::OnHit);
	OnDestroyed.AddDynamic(this, &ABMProjectile::OnDestoyedProjectile);
	
	ProjeCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ProjeCollision->CanCharacterStepUpOn =ECB_No;
	
	RootComponent = ProjeCollision;

// Mesh
	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ProjMesh->SetupAttachment(ProjeCollision);
	ProjMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>

//Particle
	ProjParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ProjParticle->SetupAttachment(ProjeCollision);
	ProjParticle->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Effect(
		TEXT("/Game/FPS_Assault_Pack/Particles/Emitters/Rifle/P_Rifle_Muzzleflash.P_Rifle_Muzzleflash"));
	if (PS_Effect.Succeeded())
	{
		ProjParticle->SetTemplate(PS_Effect.Object);
	}

	PS_Smork = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ps_smork"));
	PS_Smork->SetupAttachment(ProjeCollision);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_sm(
		TEXT("/Game/TS_Fireworks/Particles/PS_TS_FireworksShell_Palm.PS_TS_FireworksShell_Palm"));
	if (PS_sm.Succeeded())
	{
		PS_Smork->SetTemplate(PS_sm.Object);
		PS_Smork->SetRelativeLocation(FVector(0.0f, -20.0f, 0.0f));
	}


//movement
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovementComp"));
	ProjMovement->UpdatedComponent = ProjeCollision;
	ProjMovement->InitialSpeed = 3000.f;
	ProjMovement->MaxSpeed = 3000.f;
	ProjMovement->bRotationFollowsVelocity = true;
	
	//�̻��ϰ���(����)
	ProjMovement->bIsHomingProjectile = true;
	ProjMovement->HomingAccelerationMagnitude = 10000.f;




//�⺻ �����ð�
	InitialLifeSpan = 1.0f;

}

// Called when the game starts or when spawned
void ABMProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABMProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
	UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(ABMBossCharacter::StaticClass()))
	{
		FDamageEvent DamageEvent(UDamageType::StaticClass());
		OtherActor->TakeDamage(10.f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		UE_LOG(BossMode, Warning, TEXT("health : 10"));
	}

	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		ProjeCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjeCollision->SetGenerateOverlapEvents(false);
		
		ProjMesh->SetVisibility(false);

		ProjParticle->Activate();
		ProjParticle->DetachFromParent(true);

		PS_Smork->bAutoDestroy = true;
		PS_Smork->DetachFromParent(true);
	}
}

void ABMProjectile::OnDestoyedProjectile(AActor* DestoyingActor)
{
}

