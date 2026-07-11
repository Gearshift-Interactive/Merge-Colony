#include "readonly/recipes.h"

#include "common.h"
#include <string.h>

const MergeRecipe RECIPES[] = {
    {
        .inputA = "apartaments",
        .inputB = "apartaments",
        .result = "apartamentsL2",
        .cost = 100,
    }, {
        .inputA = "apartamentsL2",
        .inputB = "apartamentsL2",
        .result = "apartamentsL3",
        .cost = 250,
    }, {
        .inputA = "drill",
        .inputB = "drill",
        .result = "drillL2",
        .cost = 100,
    }, {
        .inputA = "drillL2",
        .inputB = "drillL2",
        .result = "drillL3",
        .cost = 250,
    }, {
        .inputA = "generator",
        .inputB = "generator",
        .result = "generatorL2",
        .cost = 100,
    }, {
        .inputA = "generatorL2",
        .inputB = "generatorL2",
        .result = "generatorL3",
        .cost = 250
    }, {
        .inputA = "biodome",
        .inputB = "generator",
        .result = "solarPanelL1",
        .cost = 150,
    }, {
        .inputA = "solarPanelL1",
        .inputB = "solarPanelL1",
        .result = "solarPanelL2",
        .cost = 100,
    }, {
        .inputA = "solarPanelL2",
        .inputB = "solarPanelL2",
        .result = "solarPanelL3",
        .cost = 250,
    }, {
        .inputA = "biodome",
        .inputB = "apartaments",
        .result = "bio_apartaments",
        .cost = 150,
    }, {
        .inputA = "bio_apartaments",
        .inputB = "bio_apartaments",
        .result = "bio_apartamentsL2",
        .cost = 300,
    }, {
        .inputA = "bio_apartamentsL2",
        .inputB = "bio_apartamentsL2",
        .result = "bio_apartamentsL3",
        .cost = 500
    }, {
        .inputA = "apartaments",
        .inputB = "drill",
        .result = "control",
        .cost = 150,
    }, {
        .inputA = "apartaments",
        .inputB = "generator",
        .result = "utility",
        .cost = 150,
    }, {
        .inputA = "biodome",
        .inputB = "drill",
        .result = "quiet_drillL1",
        .cost = 150,
    }, {
        .inputA = "quiet_drillL1",
        .inputB = "quiet_drillL1",
        .result = "quiet_drillL2",
        .cost = 300,
    }, {
        .inputA = "quiet_drillL2",
        .inputB = "quiet_drillL2",
        .result = "quiet_drillL3",
        .cost = 500,
    }, {
        .inputA = "generator",
        .inputB = "drill",
        .result = "miningComplexL1",
        .cost = 150,
    }, {
        .inputA = "generatorL2",
        .inputB = "drillL2",
        .result = "miningComplexL2",
        .cost = 200,
    }, {
        .inputA = "generatorL3",
        .inputB = "drillL3",
        .result = "miningComplexL3",
        .cost = 250,
    }, {
        .inputA = "miningComplexL1",
        .inputB = "miningComplexL1",
        .result = "miningComplexL2",
        .cost = 300,
    }, {
        .inputA = "miningComplexL2",
        .inputB = "miningComplexL2",
        .result = "miningComplexL3",
        .cost = 500,
    }
};
static const usize RECIPES_LEN = sizeof(RECIPES) / sizeof(RECIPES[0]);

MergeRecipe SearchRecipe(const char *inputA, const char *inputB)
{
    for (usize i = 0; i < RECIPES_LEN; i++)
        if (
            (!strcmp(RECIPES[i].inputA, inputA) && !strcmp(RECIPES[i].inputB, inputB)) ||
            (!strcmp(RECIPES[i].inputA, inputB) && !strcmp(RECIPES[i].inputB, inputA))
        ) return RECIPES[i];
    return (MergeRecipe) { 0 };
}
