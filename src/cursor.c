#pragma once

#include "textures.h"
#include "map.h"
#include "tiles.h"
#include "interface.h"

const double CURSOR_SPEED = 12.0f;
static Vector2 currentCursorPos = { 0 };
static Vector2 targetCursorPos  = { 0 };

void RenderMouseCursor(HexCoord tileSelected, u8 currentBuilding)
{
    Vector2 tileCoord = CalculateTileScreenPos(tileSelected);
    targetCursorPos = tileCoord;
    float dt = GetFrameTime();
    currentCursorPos.x += (targetCursorPos.x - currentCursorPos.x) * CURSOR_SPEED * dt;
    currentCursorPos.y += (targetCursorPos.y - currentCursorPos.y) * CURSOR_SPEED * dt;

    if (!IsTileInMap(tileSelected) || IsCursorOnGui(GetMousePosition())) return;

    if (currentBuilding)
        DrawTexture(*GetTileOutline(currentBuilding), currentCursorPos.x, currentCursorPos.y, WHITE);
    else
        DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);
}
