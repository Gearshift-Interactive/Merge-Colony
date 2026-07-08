#include "tiles.h"
#include "textures.h"
#include "string.h"

typedef struct {
    char *id;
    Texture2D *texture;
    Texture2D *outline;
    TileKind kind;
} TileData;

static TileData Tiles[] = {
    {
        .id = "void"
    }, {
        .id = "biodome",
        .texture = &TEXTURE_BIODOME,
        .outline = &TEXTURE_BIODOME_OUTLINE,
        .kind = TILE_BUILDING
    }, {
        .id = "apartaments",
        .texture = &TEXTURE_APARTAMENT,
        .outline = &TEXTURE_APARTAMENT_OUTLINE,
        .kind = TILE_BUILDING
    }, {
        .id = "drill",
        .texture = &TEXTURE_DRILL,
        .outline = &TEXTURE_DRILL_OUTLINE,
        .kind = TILE_BUILDING
    }, {
        .id = "lab",
        .texture = &TEXTURE_LAB,
        .outline = &TEXTURE_LAB_OUTLINE,
        .kind = TILE_BUILDING
    }, {
        .id = "factory",
        .texture = &TEXTURE_FACTORY,
        .outline = &TEXTURE_FACTORY_OUTLINE,
        .kind = TILE_BUILDING
    }, {
        .id = "generator",
        .texture = &TEXTURE_GENERATOR,
        .outline = &TEXTURE_GENERATOR_OUTLINE,
        .kind = TILE_BUILDING
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
