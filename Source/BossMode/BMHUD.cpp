// Fill out your copyright notice in the Description page of Project Settings.


#include "BMHUD.h"
#include "Engine/Canvas.h"

ABMHUD::ABMHUD()
{
	//�ؽ��Ŀ� ���µ��

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

	//ĵ�����߾�ã�� (x,y 0.5�� �ָ� �߾�)
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//ĵ������ �߾��� ã���� �ؽ����߽ɰ� ����� �ȴ�.
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	//CrossHair�׸���.
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

	
}
