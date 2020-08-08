// Fill out your copyright notice in the Description page of Project Settings.


#include "BMHUD.h"
#include "Engine/Canvas.h"

ABMHUD::ABMHUD()
{
	//텍스쳐에 에셋등록

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair.FirstPersonCrosshair"));
	if (CrosshiarTexObj.Succeeded())
	{
		CrosshairTex = CrosshiarTexObj.Object;
	}
}

void ABMHUD::DrawHUD()
{
	Super::DrawHUD();

	//캔버스중앙찾기 (x,y 0.5씩 주면 중앙)
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//캔버스의 중앙을 찾은후 텍스쳐중심과 맞춰야 된다.
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	//CrossHair그린다.
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

	
}
