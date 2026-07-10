#include "readonly/recipes.h"

#include "common.h"
#include <string.h>

const MergeRecipe RECIPES[] = {
    {
        .inputA = "apartaments",
        .inputB = "apartaments",
        .result = "apartamentsL2",
    }, {
        .inputA = "apartamentsL2",
        .inputB = "apartamentsL2",
        .result = "apartamentsL3",
    }, {
        .inputA = "drill",
        .inputB = "drill",
        .result = "drillL2",
    }, {
        .inputA = "drillL2",
        .inputB = "drillL2",
        .result = "drillL3",
    }
};
static const usize RECIPES_LEN = sizeof(RECIPES) / sizeof(RECIPES[0]);

const char *SearchOutput(const char *inputA, const char *inputB)
{
    for (usize i = 0; i < RECIPES_LEN; i++)
        if (
            (!strcmp(RECIPES[i].inputA, inputA) && !strcmp(RECIPES[i].inputB, inputB)) ||
            (!strcmp(RECIPES[i].inputA, inputB) && !strcmp(RECIPES[i].inputB, inputA))
        ) return RECIPES[i].result;
    return NULL;
}
