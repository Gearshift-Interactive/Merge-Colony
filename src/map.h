#pragma once

#include "common.h"

#define MAP_WIDTH  14
#define MAP_HEIGHT 10
#define MAP_LAYERS 2

#define MAP_ORIGIN_X 8
#define MAP_ORIGIN_Y 8

extern i32 CurrentOverlay;

void GenerateMars(void);
Vector2 CalculateTileScreenPos(HexCoord);
bool IsTileInMap(HexCoord);
void RenderMap(void);
u8 GetTile(u32 layer, HexCoord);
u8 GetWater(HexCoord);
u8 GetIron(HexCoord);
u8 GetCopper(HexCoord);
void SetTile(u32 layer, HexCoord, u8);
