#pragma once

#include "common.h"

#define MAP_WIDTH  14
#define MAP_HEIGHT 9
#define MAP_LAYERS 2

#define MAP_ORIGIN_X 8
#define MAP_ORIGIN_Y 8

void GenerateMars(void);
Vector2 CalculateTileScreenPos(HexCoord);
bool IsTileInMap(HexCoord);
void RenderMap(void);
u8 GetTile(u32 layer, HexCoord);
void SetTile(u32 layer, HexCoord, u8);
