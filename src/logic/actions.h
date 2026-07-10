#pragma once

#include "common.h"

extern i32 currentAction;

void UpdateActions(HexCoord mousePoint);
void DrawActions(void);
HexCoord GetMergeFrom(void);
