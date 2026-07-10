#pragma once

#include "common.h"

typedef enum {
    TILE_GROUND = 0,
    TILE_GROUND_ORE_COPPER,
    TILE_GROUND_ORE_IRON,
    TILE_BOULDER,
    TILE_MOUNTAIN,
    TILE_BUILDING_DRILL,
    TILE_BUILDING_CONTROL,
    TILE_BUILDING_APARTAMENTS,
    TILE_BUILDING_GENERATOR,
    TILE_BUILDING_BIODOME,
} TileKind;

u8 GetTileId(const char *);
Texture2D *GetTileTexture(u8 tileId);
Texture2D *GetTileOutline(u8 tileId);
TileKind GetTileKind(u8 tileId);
u32 GetTileCost(u8 tileId);
u32 GetTileSpace(u8 tileId);
i32 GetHappinessFactor(u8 tileId);
i32 GetPowerFactor(u8 tileId);
const char *GetStringId(u8 tileId);
bool TileIsBuilding(u8 tileId);
f32 GetPerformanceFactor(u8 tileId);
bool GetInternalHappinessBoost(u8 tileId);
