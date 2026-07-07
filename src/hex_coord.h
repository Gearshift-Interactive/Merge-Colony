#pragma once

#include <stdbool.h>

typedef struct {
    unsigned int x, y;
} HexCoord;

bool HexEqual(HexCoord, HexCoord);

HexCoord HexNeighbourTop(HexCoord origin);
HexCoord HexNeighbourBottom(HexCoord origin);
HexCoord HexNeighbourTopRight(HexCoord origin);
HexCoord HexNeighbourBottomRight(HexCoord origin);
HexCoord HexNeighbourTopLeft(HexCoord origin);
HexCoord HexNeighbourBottomLeft(HexCoord origin);
