#include "logic/state.h"
#include "common.h"

u32 Tehos = 1200;
u32 Population = 0;
u32 Jobs = 0;
u32 Housing = 0;
i32 Happiness = 50;

u32 Water = 1000;
u32 Food = 1000;
u32 ElectricityConsumed = 0;
u32 ElectricityGenerated = 0;

u32 Iron = 0;
u32 Copper = 1000;
u32 Uranium = 10;

void ResetState(void)
{
    Tehos = 1200;
    Population = 6;
    Happiness = 50;
    Water = 1000;
    Food = 1000;
    ElectricityConsumed = 0;
    ElectricityGenerated = 0;
    Iron = 0;
    Copper = 100000;
    Uranium = 10;
}
