// Fill out your copyright notice in the Description page of Project Settings.


#include "BMGameMode.h"
#include "BMCharacter.h"
#include "BMHUD.h"

ABMGameMode::ABMGameMode()
{
	/*static ConstructorHelpers::FClassFinder<APawn>PlayerPawnClassFinder(TEXT("/Game/FirstPersonBP/Blueprints/FirstPersonCharacter.FirstPersonCharacter_C"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;*/

	DefaultPawnClass = ABMCharacter::StaticClass();
	HUDClass = ABMHUD::StaticClass();
}