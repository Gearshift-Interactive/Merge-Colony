#pragma once

#include "textures.h"
#include "map.h"
#include "tiles.h"

void RenderMouseCursor(HexCoord tileSelected, u8 currentBuilding)
{
    if (!IsTileInMap(tileSelected)) return;
    Vector2 tileCoord = CalculateTileScreenPos(tileSelected);
    if (currentBuilding)
        DrawTexture(*GetTileOutline(currentBuilding), tileCoord.x, tileCoord.y, WHITE);
    else
        DrawTexture(TEXTURE_HIGHLIGHT, tileCoord.x, tileCoord.y, WHITE);
}
