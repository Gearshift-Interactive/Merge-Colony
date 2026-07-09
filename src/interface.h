#pragma once

#include "common.h"

static i32 selected;

void InitGui(u8 *currentTile);
void UpdateDrawGui(void);
bool IsCursorOnGui(Vector2 cursorPos);
