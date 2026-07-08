#include "map.h"

#include "tiles.h"
#include "textures.h"
#include "stb_perlin_.h"

static u8 Map[MAP_LAYERS][MAP_WIDTH][MAP_HEIGHT] = { 0 };

void GenerateMars(void)
{
    const u8 tiles[] = {
        GetTileId("void"),
        GetTileId("void"),
        GetTileId("void"),
        GetTileId("void"),
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
        GetTileId("boulder1"),
        GetTileId("boulder2"),
    };
    const size_t size = sizeof(tiles) / sizeof(tiles[0]);
    for (size_t x = 0; x < MAP_WIDTH; x++)
    for (size_t y = 0; y < MAP_HEIGHT; y++)
    {
        float perlin = stb_perlin_fbm_noise3(
            x * 0.15f, y * 0.15f, 0,
            /* lacunarity */ 2,
            /* gain */ 0.5f,
            /* octaves */ 2);
        printf("%f\n", perlin);
        if (perlin > 0)
        {
            if (perlin > 0.2f)
                SetTile(0, (HexCoord) { x, y }, GetTileId("mountain3"));
            else if (perlin > 0.1f)
                SetTile(0, (HexCoord) { x, y }, GetTileId("mountain2"));
            else
                SetTile(0, (HexCoord) { x, y }, GetTileId("mountain1"));
        }
        else
            SetTile(0, (HexCoord) { x, y }, tiles[rand() % size]);
    }
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
static void RenderTile(size_t x, size_t y)
{
    const HexCoord coord = {x, y};
    const Vector2 screenPos = CalculateTileScreenPos(coord);
    const u8 tile = GetTile(0, coord);
    if (tile)
        DrawTexture(
            *GetTileTexture(tile),
            screenPos.x,
            screenPos.y,
            WHITE
        );
}
void RenderMap(void)
{
    for (size_t y = 0; y < MAP_HEIGHT; y++)
    {
        for (size_t x = 1; x < MAP_WIDTH; x += 2)
            RenderTile(x, y);
        for (size_t x = 0; x < MAP_WIDTH; x += 2)
            RenderTile(x, y);
    }
}
u8 GetTile(u32 layer, HexCoord pos)
{
    return Map[layer][pos.x][pos.y];
}
void SetTile(u32 layer, HexCoord pos, u8 tile)
{
    Map[layer][pos.x][pos.y] = tile;
}
