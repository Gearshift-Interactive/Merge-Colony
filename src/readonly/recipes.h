#pragma once

typedef struct {
    const char *inputA;
    const char *inputB;
    const char *result;
} MergeRecipe;

extern const MergeRecipe RECIPES[];

const char *SearchOutput(const char *inputA, const char *inputB);
