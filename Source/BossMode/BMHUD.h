// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMode.h"
#include "GameFramework/HUD.h"
#include "BMHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOSSMODE_API ABMHUD : public AHUD
{
	GENERATED_BODY()
	
	ABMHUD();

public:
	virtual void DrawHUD() override;

private:
	// crosshair Asset
	class UTexture2D* CrosshairTex;
};
