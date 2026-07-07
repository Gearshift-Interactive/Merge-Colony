#pragma once

#include "common.h"

u8 GetTileId(const char *);
Texture2D *GetTileTexture(u8 tileId);
Texture2D *GetTileOutline(u8 tileId);
bool GetTileDestroyable(u8 tileId);
