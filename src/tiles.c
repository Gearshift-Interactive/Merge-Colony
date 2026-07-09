#include "tiles.h"
#include "textures.h"
#include "string.h"

typedef struct {
    char *id;
    Texture2D *texture;
    Texture2D *outline;
    TileKind kind;
    u32 space;  // how many people can live/work here
    u32 cost;  // of copper
    i32 happinessFactor;
} TileData;

static TileData Tiles[] = {
    {
        .id = "void",
    }, {
        .id = "biodome",
        .texture = &TEXTURE_BIODOME,
        .outline = &TEXTURE_BIODOME_OUTLINE,
        .kind = TILE_BUILDING_BIODOME,
        .cost = 200,
        .happinessFactor = 10,
    }, {
        .id = "apartaments",
        .texture = &TEXTURE_APARTAMENT,
        .outline = &TEXTURE_APARTAMENT_OUTLINE,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 6,
        .cost = 100,
        .happinessFactor = 3,
    }, {
        .id = "drill",
        .texture = &TEXTURE_DRILL,
        .outline = &TEXTURE_DRILL_OUTLINE,
        .kind = TILE_BUILDING_DRILL,
        .space = 3,
        .cost = 150,
        .happinessFactor = -20,
    }, {
        .id = "generator",
        .texture = &TEXTURE_GENERATOR,
        .outline = &TEXTURE_GENERATOR_OUTLINE,
        .kind = TILE_BUILDING_GENERATOR,
        .space = 3,
        .cost = 100,
        .happinessFactor = -10,
    }, {
        .id = "rocks1",
        .texture = &TEXTURE_ROCKS1,
        .kind = TILE_GROUND
    }, {
        .id = "rocks2",
        .texture = &TEXTURE_ROCKS2,
        .kind = TILE_GROUND
    }, {
        .id = "rocks3",
        .texture = &TEXTURE_ROCKS3,
        .kind = TILE_GROUND
    }, {
        .id = "copper1",
        .texture = &TEXTURE_COPPER1,
        .kind = TILE_GROUND_ORE_COPPER
    }, {
        .id = "copper2",
        .texture = &TEXTURE_COPPER2,
        .kind = TILE_GROUND_ORE_COPPER
    }, {
        .id = "iron1",
        .texture = &TEXTURE_IRON1,
        .kind = TILE_GROUND_ORE_IRON
    }, {
        .id = "iron2",
        .texture = &TEXTURE_IRON2,
        .kind = TILE_GROUND_ORE_IRON
    }, {
        .id = "mountain1-1",
        .texture = &TEXTURE_MOUNTAIN11,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain1-2",
        .texture = &TEXTURE_MOUNTAIN12,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain1-3",
        .texture = &TEXTURE_MOUNTAIN13,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain2-1",
        .texture = &TEXTURE_MOUNTAIN21,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain2-2",
        .texture = &TEXTURE_MOUNTAIN22,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain2-3",
        .texture = &TEXTURE_MOUNTAIN23,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain3-1",
        .texture = &TEXTURE_MOUNTAIN31,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain3-2",
        .texture = &TEXTURE_MOUNTAIN32,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "mountain3-3",
        .texture = &TEXTURE_MOUNTAIN33,
        .kind = TILE_MOUNTAIN
    }, {
        .id = "boulder1",
        .texture = &TEXTURE_BOULDER1,
        .kind = TILE_BOULDER
    }, {
        .id = "boulder2",
        .texture = &TEXTURE_BOULDER2,
        .kind = TILE_BOULDER
    }
};

u8 GetTileId(const char *stringId)
{
    size_t len = sizeof(Tiles) / sizeof(TileData);
    for (size_t i = 0; i < len; i++)
        if (!strcmp(Tiles[i].id, stringId))
            return i;
    return 0;
}
Texture2D *GetTileTexture(u8 tileId)
{
    return Tiles[tileId].texture;
}
Texture2D *GetTileOutline(u8 tileId)
{
    return Tiles[tileId].outline;
}
TileKind GetTileKind(u8 tileId)
{
    return Tiles[tileId].kind;
}
u32 GetTileCost(u8 tileId)
{
    return Tiles[tileId].cost;
}
u32 GetTileSpace(u8 tileId)
{
    return Tiles[tileId].space;
}
i32 GetHappinessFactor(u8 tileId)
{
    return Tiles[tileId].happinessFactor;
}
