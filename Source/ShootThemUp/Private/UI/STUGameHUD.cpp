// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUGameHUD.h"

#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawCross();
}

void ASTUGameHUD::DrawCross()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    constexpr auto HalfLineSize = 10.f;
    constexpr auto LineThickness = 2.f;
    const auto LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
