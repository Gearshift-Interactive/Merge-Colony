#pragma once

#include "common.h"

#define DESTROY_BUILDING_COST 50
#define DESTROY_BOULDER_COST  100

extern i32 currentAction;

void PerformAction(HexCoord mousePoint);
void UpdateActions(void);
void DrawActions(void);
HexCoord GetMergeFrom(void);
