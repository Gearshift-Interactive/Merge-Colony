#include "map_updater.h"

#include "map.h"
#include "tiles.h"
#include "state.h"

#define BASE_DRILL_EFFICENSY 5  // for 255
#define BASE_HAPPINESS 50

static float globalEfficency = 1;
static u8 ticksSincePopulationTick = 0;

static void UpdateBuildingDrill(HexCoord pos)
{
    u8 copper = GetCopper(pos);
    if (copper) Copper += round(BASE_DRILL_EFFICENSY * (copper / 255.0f) * globalEfficency);
    u8 iron = GetIron(pos);
    if (iron) Iron += round(BASE_DRILL_EFFICENSY * (iron / 255.0f) * globalEfficency);
    u8 water = GetWater(pos);
    if (water) water += round(BASE_DRILL_EFFICENSY * (water / 255.0f) * globalEfficency);
}
static void UpdateTile(HexCoord pos)
{
    switch (GetTileKind(GetTile(1, pos)))
    {
    case TILE_BUILDING_DRILL: UpdateBuildingDrill(pos); break;
    default: break;
    }
}

static u8 CheckHappiness(HexCoord pos)
{
    u8 happiness = BASE_HAPPINESS;
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTop(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTopRight(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottomRight(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottom(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourBottomLeft(pos)));
    happiness += GetHappinessFactor(GetTile(1, HexNeighbourTopLeft(pos)));
    return happiness;
}
static void UpdateJobsAndHousing(void)
{
    Jobs = 0;
    Housing = 0;
    for (usize x = 0; x < MAP_WIDTH; x++)
    for (usize y = 0; y < MAP_HEIGHT; y++)
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
    if (Jobs <= Population) globalEfficency = 1;
    else globalEfficency = (float)Population / (float)Jobs;
}

static void PopulationTick(void)
{
    const float occupancy = (float)Population / (float)Housing;
    u32 happinessCount = 0;
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

    UpdateJobsAndHousing();

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
