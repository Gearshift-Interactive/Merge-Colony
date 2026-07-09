#include "map_updater.h"

#include "map.h"
#include "tiles.h"
#include "state.h"

#define BASE_DRILL_EFFICENSY 10  // 10 for 255

void UpdateBuildingDrill(HexCoord pos)
{
    u8 copper = GetCopper(pos);
    if (copper) Copper += BASE_DRILL_EFFICENSY * (copper / 255.0f);
    u8 iron = GetIron(pos);
    if (copper) Iron += BASE_DRILL_EFFICENSY * (iron / 255.0f);
    u8 water = GetWater(pos);
    if (water) water += BASE_DRILL_EFFICENSY * (water / 255.0f);
}

void UpdateTile(HexCoord pos)
{
    switch (GetTileKind(GetTile(1, pos)))
    {
        case TILE_BUILDING_DRILL: UpdateBuildingDrill(pos); break;
        default: break;
    }
}

void UpdateMap(void)
{
    for (usize x = 0; x < MAP_WIDTH; x++)
    for (usize y = 0; y < MAP_HEIGHT; y++)
        UpdateTile((HexCoord) { x, y });
}
