#pragma once

#include "common.h"

typedef enum {
    TILE_GROUND = 0,
    TILE_GROUND_ORE_COPPER,
    TILE_GROUND_ORE_IRON,
    TILE_BUILDING,
    TILE_BOULDER,
    TILE_MOUNTAIN,
} TileKind;

u8 GetTileId(const char *);
Texture2D *GetTileTexture(u8 tileId);
Texture2D *GetTileOutline(u8 tileId);
TileKind GetTileKind(u8 tileId);
u32 GetTileCost(u8 tileId);
