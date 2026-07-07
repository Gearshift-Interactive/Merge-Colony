#pragma once

#include "common.h"

#define MAP_WIDTH  14
#define MAP_HEIGHT 9

void GenerateMars(void);
u8 GetTile(HexCoord);
void SetTile(HexCoord, u8);
