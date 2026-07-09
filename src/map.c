#include "map.h"

#include "tiles.h"
#include "textures.h"
#include "stb_perlin_.h"

#define MAX_COPPER 5
#define MAX_IRON 3

static u8 Map[MAP_LAYERS][MAP_WIDTH][MAP_HEIGHT] = { 0 };

i32 CurrentOverlay = 0;

static u8 Copper[MAP_WIDTH][MAP_HEIGHT] = { 0 };
static u8 Iron[MAP_WIDTH][MAP_HEIGHT] = { 0 };
static u8 Water[MAP_WIDTH][MAP_HEIGHT] = { 0 };

static HexCoord FindFree()
{
    HexCoord result =  { rand() % MAP_WIDTH, rand() % MAP_HEIGHT };
    if (GetTile(1, result)) return FindFree();
    return result;
}

void GenerateMars(void)
{
    const u8 tiles[] = {
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
    };
    const usize tiles_size = sizeof(tiles) / sizeof(tiles[0]);
    const u8 boulders[] = {
        GetTileId("boulder1"),
        GetTileId("boulder2"),
    };
    const usize boulders_size = sizeof(boulders) / sizeof(boulders[0]);
    const u8 mountains1[] = {
        GetTileId("mountain1-1"),
        GetTileId("mountain1-2"),
        GetTileId("mountain1-3"),
    };
    const usize mountains1_size = sizeof(mountains1) / sizeof(mountains1[0]);
    const u8 mountains2[] = {
        GetTileId("mountain2-1"),
        GetTileId("mountain2-2"),
        GetTileId("mountain2-3"),
    };
    const usize mountains2_size = sizeof(mountains2) / sizeof(mountains2[0]);
    const u8 mountains3[] = {
        GetTileId("mountain3-1"),
        GetTileId("mountain3-2"),
        GetTileId("mountain3-3"),
    };
    const usize mountains3_size = sizeof(mountains3) / sizeof(mountains3[0]);
    for (size_t x = 0; x < MAP_WIDTH; x++)
    for (size_t y = 0; y < MAP_HEIGHT; y++)
    {
        f32 perlin = stb_perlin_fbm_noise3(
            x * 0.15f, y * 0.15f, 0,
            /* lacunarity */ 2,
            /* gain */ 0.5f,
            /* octaves */ 2
        );
        if (perlin > -0.1f)
        {
            if (perlin > 0.3f)
                SetTile(1, (HexCoord) { x, y }, mountains3[rand() % mountains3_size]);
            else if (perlin > 0.15f)
                SetTile(1, (HexCoord) { x, y }, mountains2[rand() % mountains2_size]);
            else if (perlin > 0)
                SetTile(1, (HexCoord) { x, y }, mountains1[rand() % mountains1_size]);
            else
                SetTile(1, (HexCoord) { x, y }, boulders[rand() % boulders_size]);
        }
        else
            SetTile(1, (HexCoord) { x, y }, 0);
        SetTile(0, (HexCoord) { x, y }, tiles[rand() % tiles_size]);

        f32 copperPerlin = stb_perlin_fbm_noise3(
            x * 0.15f, y * 0.15f, 10000,
            /* lacunarity */ 2,
            /* gain */ 0.7f,
            /* octaves */ 4
        );
        if (copperPerlin > 0)
            Copper[x][y] = copperPerlin * 255;
        f32 ironPerlin = stb_perlin_fbm_noise3(
            x * 0.15f, y * 0.15f, 20000,
            /* lacunarity */ 2,
            /* gain */ 0.2f,
            /* octaves */ 8
        );
        if (ironPerlin > 0.1f)
            Iron[x][y] = (ironPerlin - 0.1f) / 0.9f * 255;
        f32 waterPerlin = stb_perlin_fbm_noise3(
            x * 0.15f, y * 0.15f, 30000,
            /* lacunarity */ 2,
            /* gain */ 0.5f,
            /* octaves */ 2
        );
        if (waterPerlin > 0)
            Water[x][y] = waterPerlin * 255;
    }
    // const u8 coppers[] = {
    //     GetTileId("copper1"),
    //     GetTileId("copper2"),
    // };
    // const usize coppers_size = sizeof(coppers) / sizeof(coppers[0]);
    // for (usize i = 0; i < MAX_COPPER; i++)
    //     SetTile(0, FindFree(), coppers[rand() % coppers_size]);
    // const u8 irons[] = {
    //     GetTileId("iron1"),
    //     GetTileId("iron2"),
    // };
    // const usize ironsSize = sizeof(irons) / sizeof(irons[0]);
    // for (usize i = 0; i < MAX_IRON; i++)
    //     SetTile(0, FindFree(), irons[rand() % ironsSize]);
}
Vector2 CalculateTileScreenPos(HexCoord coord)
{
    return (Vector2) {
        MAP_ORIGIN_X + TEXTURE_HIGHLIGHT.width * 0.75f * coord.x,
        MAP_ORIGIN_Y - TEXTURE_HIGHLIGHT.height * 0.5f + TEXTURE_HIGHLIGHT.height * coord.y + ( (coord.x % 2 == 0)
            ? TEXTURE_HIGHLIGHT.height / 2
            : 0
        )
    };
}
bool IsTileInMap(HexCoord coord)
{
    return coord.x >= 0 && coord.y >= 0 && coord.x < MAP_WIDTH && coord.y < MAP_HEIGHT;
}
static void RenderTile(int layer, size_t x, size_t y)
{
    const HexCoord coord = {x, y};
    const Vector2 screenPos = CalculateTileScreenPos(coord);
    const u8 tile = GetTile(layer, coord);
    if (tile)
        DrawTexture(
            *GetTileTexture(tile),
            screenPos.x,
            screenPos.y,
            WHITE
        );
}
static void RenderOverlay(size_t x, size_t y)
{
    if (!CurrentOverlay)
        return;
    Color color = { 0 };
    switch(CurrentOverlay)
    {
    case 1:
        color.r = 10;
        color.g = 120;
        color.b = 230;
        color.a = Water[x][y];
        break;
    case 2:
        color.r = 9;
        color.g = 28;
        color.b = 52;
        color.a = Iron[x][y];
        break;
    case 3:
        color.r = 101;
        color.g = 240;
        color.b = 196;
        color.a = Copper[x][y];
        break;
    }

    const HexCoord coord = {x, y};
    const Vector2 screenPos = CalculateTileScreenPos(coord);
    DrawTexture(TEXTURE_HEX, screenPos.x, screenPos.y + TEXTURE_HEX.height * 0.5f, color);
}
void RenderMap(void)
{
    for (size_t y = 0; y < MAP_HEIGHT; y++)
    {
        for (size_t x = 1; x < MAP_WIDTH; x += 2)
            for (int layer = 0; layer < 2; layer++)
                RenderTile(layer, x, y);
        for (size_t x = 0; x < MAP_WIDTH; x += 2)
            for (int layer = 0; layer < 2; layer++)
                RenderTile(layer, x, y);
    }
    for (size_t y = 0; y < MAP_HEIGHT; y++)
        for (size_t x = 0; x < MAP_WIDTH; x++)
            RenderOverlay(x, y);
}
u8 GetTile(u32 layer, HexCoord pos)
{
    return Map[layer][pos.x][pos.y];
}
void SetTile(u32 layer, HexCoord pos, u8 tile)
{
    Map[layer][pos.x][pos.y] = tile;
}
