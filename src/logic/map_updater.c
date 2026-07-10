#include "logic/map_updater.h"

#include "logic/map.h"
#include "readonly/tiles.h"
#include "logic/state.h"

#define BASE_DRILL_EFFICENSY 5  // for 255
#define BASE_HAPPINESS 50
#define MAX_POWER_HAPPINESS_DEBUFF 20

static f32 populationEfficency = 1;
static u8 ticksSincePopulationTick = 0;
static f32 powerRatio = 1;

static f32 CheckDrillPerformance(HexCoord pos)
{
    f32 result = GetPerformanceFactor(GetTile(1, pos));
    if (GetTileKind(GetTile(1, HexNeighbourTop(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourTop(pos)));
    if (GetTileKind(GetTile(1, HexNeighbourTopRight(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourTopRight(pos)));
    if (GetTileKind(GetTile(1, HexNeighbourBottomRight(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourBottomRight(pos)));
    if (GetTileKind(GetTile(1, HexNeighbourBottom(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourBottom(pos)));
    if (GetTileKind(GetTile(1, HexNeighbourBottomLeft(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourBottomLeft(pos)));
    if (GetTileKind(GetTile(1, HexNeighbourTopLeft(pos))) == TILE_BUILDING_CONTROL)
        result *= GetPerformanceFactor(GetTile(1, HexNeighbourTopLeft(pos)));
    return result;
}
static void UpdateBuildingDrill(HexCoord pos)
{
    f32 const PERFORMANCE_FACTOR = CheckDrillPerformance(pos);
    u8 copper = GetCopper(pos);
    if (copper) Copper += round(BASE_DRILL_EFFICENSY * (copper / 255.0f) * populationEfficency * powerRatio * PERFORMANCE_FACTOR);
    u8 iron = GetIron(pos);
    if (iron) Iron += round(BASE_DRILL_EFFICENSY * (iron / 255.0f) * populationEfficency * powerRatio * PERFORMANCE_FACTOR);
    // u8 water = GetWater(pos);
    // if (water) water += round(BASE_DRILL_EFFICENSY * (water / 255.0f) * populationEfficency * powerRatio);
}
static void UpdateTile(HexCoord pos)
{
    switch (GetTileKind(GetTile(1, pos)))
    {
    case TILE_BUILDING_DRILL: UpdateBuildingDrill(pos); break;
    default: break;
    }
}

u8 CheckHappiness(HexCoord pos)
{
    u8 happiness = BASE_HAPPINESS - (1.0f - powerRatio) * MAX_POWER_HAPPINESS_DEBUFF;
    if (GetInternalHappinessBoost(GetTile(1, pos))) happiness += GetHappinessFactor(GetTile(1, pos));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTop(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTopRight(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottomRight(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottom(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottomLeft(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTopLeft(pos)));
    return happiness;
}
static void UpdateJobsHousingAndElectricity(void)
{
    ElectricityGenerated = 0;
    ElectricityConsumed = 0;
    Jobs = 0;
    Housing = 0;
    for (usize x = 0; x < MAP_WIDTH; x++)
    for (usize y = 0; y < MAP_HEIGHT; y++)
    {
        switch (GetTileKind(GetTile(1, (HexCoord) { x, y })))
        {
        case TILE_BUILDING_DRILL:
        case TILE_BUILDING_GENERATOR:
            Jobs += GetTileSpace(GetTile(1, (HexCoord) { x, y }));
            break;
        case TILE_BUILDING_APARTAMENTS:
            Housing += GetTileSpace(GetTile(1, (HexCoord) { x, y }));
            break;
        default:
            break;
        }
        i32 powerFactor = GetPowerFactor(GetTile(1, (HexCoord) { x, y }));
        if (powerFactor > 0)
            ElectricityGenerated += powerFactor;
        else if (powerFactor < 0)
            ElectricityConsumed -= powerFactor;
    }
    if (Jobs <= Population) populationEfficency = 1;
    else populationEfficency = (float)Population / (float)Jobs;

    powerRatio = (float)ElectricityGenerated / (float)ElectricityConsumed;
    if (powerRatio > 1) powerRatio = 1;
}

static void PopulationTick(void)
{
    const float occupancy = (float)Population / (float)Housing;
    u32 happinessCount = 0;
    // Calculate happiness
    for (usize x = 0; x < MAP_WIDTH; x++)
    for (usize y = 0; y < MAP_HEIGHT; y++)
        if (GetTileKind(GetTile(1, (HexCoord) { x, y })) == TILE_BUILDING_APARTAMENTS)
            happinessCount += CheckHappiness((HexCoord) { x, y }) *
                GetTileSpace(GetTile(1, (HexCoord) { x, y })) * occupancy;
    if (Population) Happiness = happinessCount / Population;
    else Happiness = BASE_HAPPINESS;

    Population += round(((float)Happiness - 45.0f) / 10.0f);
    if (Population > Housing) Population = Housing;
    if (Population < 0) Population = 0;
}

void UpdateMap(void)
{
    if (Population > Housing) Population = Housing;

    UpdateJobsHousingAndElectricity();

    ticksSincePopulationTick++;
    if (ticksSincePopulationTick >= 5)
    {
        ticksSincePopulationTick -= 5;
        PopulationTick();
    }

    for (usize x = 0; x < MAP_WIDTH; x++)
    for (usize y = 0; y < MAP_HEIGHT; y++)
        UpdateTile((HexCoord) { x, y });
}
