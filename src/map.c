#include "map.h"

static u8 Map[MAP_WIDTH][MAP_HEIGHT] = { 0 };

u8 GetTile(HexCoord pos)
{
    return Map[pos.x][pos.y];
}
void SetTile(HexCoord pos, u8 tile)
{
    Map[pos.x][pos.y] = tile;
}
