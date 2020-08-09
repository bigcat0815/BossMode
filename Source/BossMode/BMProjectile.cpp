// Fill out your copyright notice in the Description page of Project Settings.


#include "BMProjectile.h"
//#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABMProjectile::ABMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// 발사체의 콜리전 처리
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

//movement
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovementComp"));
	ProjMovement->UpdatedComponent = ProjeCollision;
	ProjMovement->InitialSpeed = 3000.f;
	ProjMovement->MaxSpeed = 3000.f;
	ProjMovement->bRotationFollowsVelocity = true;
	
	//미사일관련(추적)
	ProjMovement->bIsHomingProjectile = true;
	ProjMovement->HomingAccelerationMagnitude = 10000.f;

//기본 삭제시간
	InitialLifeSpan = 3.0f;

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

void ABMProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		ProjeCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjeCollision->SetGenerateOverlapEvents(false);
		
		ProjMesh->SetVisibility(false);

		ProjParticle->Activate();
		ProjParticle->DetachFromParent(true);

	}
}

void ABMProjectile::OnDestoyedProjectile(AActor* DestoyingActor)
{
}

