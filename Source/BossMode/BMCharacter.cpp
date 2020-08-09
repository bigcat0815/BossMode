// Fill out your copyright notice in the Description page of Project Settings.


#include "BMCharacter.h"
#include "BMProjectile.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABMCharacter::ABMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FPCameraComponent->bUsePawnControlRotation = true;

	
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->SetupAttachment(FPCameraComponent);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;

	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);
	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;
	FPGunMesh->AttachTo(FPMesh, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);

	//발사체
	ProjSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjSpawn->SetupAttachment(FPGunMesh);
}

// Called when the game starts or when spawned
void ABMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABMCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABMCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ABMCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ABMCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ABMCharacter::OnFire);

	//유도미사일
	PlayerInputComponent->BindAction(TEXT("Track"), EInputEvent::IE_Pressed, this, &ABMCharacter::OnTrack);
}

void ABMCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABMCharacter::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ABMCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::OnFire()
{
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() !=nullptr)
		{
			
			ABMProjectile* ThisProjectile = GetWorld()->SpawnActor<ABMProjectile>(ProjectileClass,
				ProjSpawn->GetComponentLocation(), ProjSpawn->GetComponentRotation());
			ThisProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;
		}
	}
}

void ABMCharacter::OnTrack()
{
	FVector MousePos;
	FVector MouseDir;
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParms;
	ObjectQueryParms.AddObjectTypesToQuery(ECC_GameTraceChannel3);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	if (GEngine->GameViewport != nullptr && PlayerController != nullptr)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();
		
		PlayerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePos, MouseDir);
		MouseDir *= 100000.f;

		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParms);
	}

	if (Hit.bBlockingHit)
	{
		UE_LOG(BossMode, Warning, TEXT("Trace Hit Whit %s"), *(Hit.GetActor()->GetName()));
		TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));
	}
	else
	{
		UE_LOG(BossMode, Warning, TEXT("No Trace"));
		TrackingSceneComponent = nullptr;
	}
}

