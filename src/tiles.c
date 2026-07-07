#include "tiles.h"
#include "textures.h"
#include "string.h"

typedef struct {
    char *id;
    Texture2D *texture;
} TileData;

static TileData Tiles[] = {
    {
        .id = "void"
    }, {
        .id = "biodome",
        .texture = &TEXTURE_BIODOME
    }, {
        .id = "apartaments",
        .texture = &TEXTURE_APARTAMENT
    }, {
        .id = "drill",
        .texture = &TEXTURE_DRILL
    }, {
        .id = "lab",
        // .texture = &TEXTURE_LAB
    }, {
        .id = "factory",
        .texture = &TEXTURE_FACTORY
    }, {
        .id = "generator",
        // .texture = &TEXTURE_GENERATOR
    }, {
        .id = "rocks1",
        .texture = &TEXTURE_ROCKS1
    }, {
        .id = "rocks2",
        .texture = &TEXTURE_ROCKS2
    }, {
        .id = "rocks3",
        .texture = &TEXTURE_ROCKS3
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
