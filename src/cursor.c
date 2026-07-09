#pragma once

#include "textures.h"
#include "map.h"
#include "tiles.h"
#include "interface.h"
#include "state.h"

const double CURSOR_SPEED = 12.0f;
static Vector2 currentCursorPos = { 0 };
static Vector2 targetCursorPos  = { 0 };

void RenderMouseCursor(HexCoord tileSelected, u8 currentBuilding)
{
    if (!IsTileInMap(tileSelected) || IsCursorOnGui(GetMousePosition())) return;

    Vector2 tileCoord = CalculateTileScreenPos(tileSelected);
    targetCursorPos = tileCoord;
    float dt = GetFrameTime();
    currentCursorPos.x += (targetCursorPos.x - currentCursorPos.x) * CURSOR_SPEED * dt;
    currentCursorPos.y += (targetCursorPos.y - currentCursorPos.y) * CURSOR_SPEED * dt;

    if (currentBuilding)
        if (GetTile(1, tileSelected))
            DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
        else
        {
            DrawTexture(*GetTileOutline(currentBuilding), currentCursorPos.x, currentCursorPos.y, WHITE);
            u32 cost = GetTileCost(currentBuilding);
            Color color = (Copper >= cost) ? RAYWHITE : RED;
            const char *text = TextFormat("%d", cost);
            DrawText(text, currentCursorPos.x + 16, currentCursorPos.y + 4, 8, color);
            GuiDrawIcon(15, currentCursorPos.x, currentCursorPos.y, 1, color);
            return;
        }
    else
        DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);

    if (!CurrentOverlay)
    {
        GuiDisableTooltip();
        return;
    }

    u8 data = 0;
    switch (CurrentOverlay)
    {
        // case 1:
        //     data = GetWater(tileSelected);
        //     break;
        case 1:
            data = GetCopper(tileSelected);
            break;
        case 2:
            data = GetIron(tileSelected);
            break;
    }
    if (data)
    {
        const char *text = TextFormat("%.2f%%", data / 255.0f * 100);
        DrawText(text, currentCursorPos.x, currentCursorPos.y, GuiGetFont().baseSize, RAYWHITE);
    }
}
