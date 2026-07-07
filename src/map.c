#include "map.h"

#include "tiles.h"

static u8 Map[MAP_WIDTH][MAP_HEIGHT] = { 0 };

void GenerateMars(void)
{
    const u8 tiles[] = {
        GetTileId("void"),
        GetTileId("rocks1"),
        GetTileId("rocks2"),
        GetTileId("rocks3"),
    };
    const size_t size = sizeof(tiles) / sizeof(tiles[0]);
    for (size_t x = 0; x < MAP_WIDTH; x++)
    for (size_t y = 0; y < MAP_HEIGHT; y++)
        SetTile((HexCoord) { x, y }, tiles[rand() % size]);
}
u8 GetTile(HexCoord pos)
{
    return Map[pos.x][pos.y];
}
void SetTile(HexCoord pos, u8 tile)
{
    Map[pos.x][pos.y] = tile;
}
