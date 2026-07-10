#pragma once

#include "common.h"

typedef struct {
    const char *inputA;
    const char *inputB;
    const char *result;
    u16 cost; // iron
} MergeRecipe;

extern const MergeRecipe RECIPES[];

MergeRecipe SearchRecipe(const char *inputA, const char *inputB);
