#include "tiles.h"
#include "textures.h"
#include "string.h"

typedef struct {
    char *id;
    Texture2D *texture;
    Texture2D *outline;
    bool destroyable;
} TileData;

static TileData Tiles[] = {
    {
        .id = "void"
    }, {
        .id = "biodome",
        .texture = &TEXTURE_BIODOME,
        .outline = &TEXTURE_BIODOME_OUTLINE,
        .destroyable = true
    }, {
        .id = "apartaments",
        .texture = &TEXTURE_APARTAMENT,
        .outline = &TEXTURE_APARTAMENT_OUTLINE,
        .destroyable = true
    }, {
        .id = "drill",
        .texture = &TEXTURE_DRILL,
        .outline = &TEXTURE_DRILL_OUTLINE,
        .destroyable = true
    }, {
        .id = "lab",
        // .texture = &TEXTURE_LAB,
        // .outline = &TEXTURE_OUTLINE_OUTLINE,
        .destroyable = true
    }, {
        .id = "factory",
        .texture = &TEXTURE_FACTORY,
        .outline = &TEXTURE_FACTORY_OUTLINE,
        .destroyable = true
    }, {
        .id = "generator",
        // .texture = &TEXTURE_GENERATOR,
        // .outline = &TEXTURE_GENERATOR_OUTLINE,
        .destroyable = true
    }, {
        .id = "rocks1",
        .texture = &TEXTURE_ROCKS1
    }, {
        .id = "rocks2",
        .texture = &TEXTURE_ROCKS2
    }, {
        .id = "rocks3",
        .texture = &TEXTURE_ROCKS3
    }, {
        .id = "mountain1",
        .texture = &TEXTURE_MOUNTAIN1
    }, {
        .id = "mountain2",
        .texture = &TEXTURE_MOUNTAIN2
    }, {
        .id = "mountain3",
        .texture = &TEXTURE_MOUNTAIN3
    }, {
        .id = "boulder1",
        .texture = &TEXTURE_BOULDER1,
        .destroyable = true
    }, {
        .id = "boulder2",
        .texture = &TEXTURE_BOULDER2,
        .destroyable = true
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
bool GetTileDestroyable(u8 tileId)
{
    return Tiles[tileId].destroyable;
}
