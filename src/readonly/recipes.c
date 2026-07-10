#include "readonly/recipes.h"

const MergeRecipe recipes[] = {
    {
        .inputA = "apartaments",
        .inputB = "apartaments",
        .result = "apartamentsL2",
    }, {
        .inputA = "apartamentsL2",
        .inputB = "apartamentsL2",
        .result = "apartamentsL3",
    },
};
