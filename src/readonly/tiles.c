#include "readonly/tiles.h"
#include "readonly/textures.h"
#include <string.h>

typedef struct {
    char *id;
    Texture2D *texture;
    Texture2D *outline;
    TileKind kind;
    u32 space;  // how many people can live/work here
    u32 cost;  // of copper
    i32 happinessFactor;
    i32 powerFactor;
    f32 performanceFactor;
    bool internalHappinessBoost;
    char *name;
    char *comment;
} TileData;

static const TileKind Buildings[] = {
    TILE_BUILDING_DRILL,
    TILE_BUILDING_APARTAMENTS,
    TILE_BUILDING_GENERATOR,
    TILE_BUILDING_BIODOME,
    TILE_BUILDING_CONTROL,
};
static const usize BUILDINGS_LEN = sizeof(Buildings) / sizeof(Buildings[0]);

static const TileData Tiles[] = {
    {
        .id = "void",
    }, {
        .name = "Biodome",
        .comment = "Increases happiness for nearby apartaments.",
        .id = "biodome",
        .texture = &TEXTURE_BIODOME,
        .outline = &TEXTURE_BIODOME_OUTLINE,
        .kind = TILE_BUILDING_BIODOME,
        .cost = 200,
        .happinessFactor = 10,
        .powerFactor = -20,
    }, {
        .name = "Habitat Level 1",
        .comment = "Houses people.",
        .id = "apartaments",
        .texture = &TEXTURE_APARTAMENT,
        .outline = &TEXTURE_APARTAMENT_OUTLINE,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 6,
        .cost = 100,
        .happinessFactor = 3,
        .powerFactor = -20,
    }, {
        .name = "Habitat Level 2",
        .comment = "Houses people.",
        .id = "apartamentsL2",
        .texture = &TEXTURE_APARTAMENTL2,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 12,
        .happinessFactor = 3,
        .powerFactor = -30,
    }, {
        .name = "Habitat Level 3",
        .comment = "Houses people.",
        .id = "apartamentsL3",
        .texture = &TEXTURE_APARTAMENTL3,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 24,
        .happinessFactor = 6,
        .powerFactor = -40,
    }, {
        .name = "Eden Habitat Level 1",
        .comment = "Houses people with increased happiness by default.",
        .id = "bio_apartaments",
        .texture = &TEXTURE_BIO_APARTAMENT,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 6,
        .happinessFactor = 13,
        .powerFactor = -40,
        .internalHappinessBoost = true,
    }, {
        .name = "Eden Habitat Level 2",
        .comment = "Houses people with increased happiness by default.",
        .id = "bio_apartamentsL2",
        .texture = &TEXTURE_BIO_APARTAMENTL2,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 12,
        .happinessFactor = 13,
        .powerFactor = -50,
        .internalHappinessBoost = true,
    }, {
        .name = "Eden Habitat Level 3",
        .comment = "Houses people with increased happiness by default.",
        .id = "bio_apartamentsL3",
        .texture = &TEXTURE_BIO_APARTAMENTL3,
        .kind = TILE_BUILDING_APARTAMENTS,
        .space = 24,
        .happinessFactor = 16,
        .powerFactor = -60,
        .internalHappinessBoost = true,
    }, {
        .name = "Drill Level 1",
        .comment = "Mines resources up from the ground.",
        .id = "drill",
        .texture = &TEXTURE_DRILL,
        .outline = &TEXTURE_DRILL_OUTLINE,
        .kind = TILE_BUILDING_DRILL,
        .space = 3,
        .cost = 150,
        .happinessFactor = -20,
        .powerFactor = -50,
        .performanceFactor = 1.0f,
    }, {
        .name = "Drill Level 2",
        .comment = "Mines resources up from the ground.",
        .id = "drillL2",
        .texture = &TEXTURE_DRILLL2,
        .kind = TILE_BUILDING_DRILL,
        .space = 5,
        .happinessFactor = -30,
        .powerFactor = -80,
        .performanceFactor = 2.0f,
    }, {
        .name = "Drill Level 3",
        .comment = "Mines resources up from the ground.",
        .id = "drillL3",
        .texture = &TEXTURE_DRILLL3,
        .kind = TILE_BUILDING_DRILL,
        .space = 10,
        .happinessFactor = -40,
        .powerFactor = -140,
        .performanceFactor = 3.0f,
    }, {
        .name = "Quiet Drill Level 1",
        .comment = "Mines resources up from the ground with much less noise.",
        .id = "quiet_drillL1",
        .texture = &TEXTURE_QUIET_DRILL,
        .kind = TILE_BUILDING_DRILL,
        .space = 3,
        .happinessFactor = -3,
        .powerFactor = -75,
        .performanceFactor = 0.75f,
    }, {
        .name = "Quiet Drill Level 2",
        .comment = "Mines resources up from the ground with much less noise.",
        .id = "quiet_drillL2",
        .texture = &TEXTURE_QUIET_DRILLL2,
        .kind = TILE_BUILDING_DRILL,
        .space = 5,
        .happinessFactor = -6,
        .powerFactor = -120,
        .performanceFactor = 1.5f,
    }, {
        .name = "Quiet Drill Level 3",
        .comment = "Mines resources up from the ground with much less noise.",
        .id = "quiet_drillL3",
        .texture = &TEXTURE_QUIET_DRILLL3,
        .kind = TILE_BUILDING_DRILL,
        .space = 10,
        .happinessFactor = -9,
        .powerFactor = -210,
        .performanceFactor = 2.25f,
    }, {
        .name = "Control Centre",
        .comment = "Increases efficiency for nearby drills.",
        .id = "control",
        .texture = &TEXTURE_CONTROL,
        .kind = TILE_BUILDING_CONTROL,
        .space = 10,
        .happinessFactor = -10,
        .powerFactor = -20,
        .performanceFactor = 1.5f,
    }, {
        .name = "Utility Hub",
        .comment = "Increases efficiency for nearby generators.",
        .id = "utility",
        .texture = &TEXTURE_UTILITY_HUB,
        .kind = TILE_BUILDING_UTILITY,
        .space = 10,
        .happinessFactor = -10,
        .powerFactor = -20,
        .performanceFactor = 1.5f,
    }, {
        .name = "Generator Level 1",
        .comment = "Generates electricity.",
        .id = "generator",
        .texture = &TEXTURE_GENERATOR,
        .outline = &TEXTURE_GENERATOR_OUTLINE,
        .kind = TILE_BUILDING_GENERATOR,
        .space = 3,
        .cost = 150,
        .happinessFactor = -10,
        .powerFactor = 200,
    }, {
        .name = "Generator Level 2",
        .comment = "Generates electricity.",
        .id = "generatorL2",
        .texture = &TEXTURE_GENERATORL2,
        .kind = TILE_BUILDING_GENERATOR,
        .space = 5,
        .happinessFactor = -30,
        .powerFactor = 400,
    }, {
        .name = "Generator Level 3",
        .comment = "Generates electricity.",
        .id = "generatorL3",
        .texture = &TEXTURE_GENERATORL3,
        .kind = TILE_BUILDING_GENERATOR,
        .space = 10,
        .happinessFactor = -40,
        .powerFactor = 800,
    }, {
        .name = "Solar Panel Level 1",
        .comment = "Generates electricity with much less noise.",
        .id = "solarPanelL1",
        .texture = &TEXTURE_SOLAR_PANEL,
        .kind = TILE_BUILDING_GENERATOR,
        .powerFactor = 150,
    }, {
        .name = "Solar Panel Level 2",
        .comment = "Generates electricity with much less noise.",
        .id = "solarPanelL2",
        .texture = &TEXTURE_SOLAR_PANELL2,
        .kind = TILE_BUILDING_GENERATOR,
        .powerFactor = 300,
    }, {
        .name = "Solar Panel Level 3",
        .comment = "Generates electricity with much less noise.",
        .id = "solarPanelL3",
        .texture = &TEXTURE_SOLAR_PANELL3,
        .kind = TILE_BUILDING_GENERATOR,
        .powerFactor = 600,
    }, {
        .id = "rocks1",
        .texture = &TEXTURE_ROCKS1,
        .kind = TILE_GROUND
    }, {
        .id = "rocks2",
        .texture = &TEXTURE_ROCKS2,
        .kind = TILE_GROUND
    }, {
        .id = "rocks3",
        .texture = &TEXTURE_ROCKS3,
        .kind = TILE_GROUND
    }, {
        .id = "copper1",
        .texture = &TEXTURE_COPPER1,
        .kind = TILE_GROUND_ORE_COPPER
    }, {
        .id = "copper2",
        .texture = &TEXTURE_COPPER2,
        .kind = TILE_GROUND_ORE_COPPER
    }, {
        .id = "iron1",
        .texture = &TEXTURE_IRON1,
        .kind = TILE_GROUND_ORE_IRON
    }, {
        .id = "iron2",
        .texture = &TEXTURE_IRON2,
        .kind = TILE_GROUND_ORE_IRON
    }, {
        .name = "Small Mountain",
        .comment = "Impassable.",
        .id = "mountain1-1",
        .texture = &TEXTURE_MOUNTAIN11,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Small Mountain",
        .comment = "Impassable.",
        .id = "mountain1-2",
        .texture = &TEXTURE_MOUNTAIN12,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Small Mountain",
        .comment = "Impassable.",
        .id = "mountain1-3",
        .texture = &TEXTURE_MOUNTAIN13,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Medium Mountain",
        .comment = "Impassable.",
        .id = "mountain2-1",
        .texture = &TEXTURE_MOUNTAIN21,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Medium Mountain",
        .comment = "Impassable.",
        .id = "mountain2-2",
        .texture = &TEXTURE_MOUNTAIN22,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Medium Mountain",
        .comment = "Impassable.",
        .id = "mountain2-3",
        .texture = &TEXTURE_MOUNTAIN23,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Big Mountain",
        .comment = "Impassable.",
        .id = "mountain3-1",
        .texture = &TEXTURE_MOUNTAIN31,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Big Mountain",
        .comment = "Impassable.",
        .id = "mountain3-2",
        .texture = &TEXTURE_MOUNTAIN32,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Big Mountain",
        .comment = "Impassable.",
        .id = "mountain3-3",
        .texture = &TEXTURE_MOUNTAIN33,
        .kind = TILE_MOUNTAIN
    }, {
        .name = "Boulder",
        .comment = "Somewhat passable.",
        .id = "boulder1",
        .texture = &TEXTURE_BOULDER1,
        .kind = TILE_BOULDER
    }, {
        .name = "Boulder",
        .comment = "Somewhat passable.",
        .id = "boulder2",
        .texture = &TEXTURE_BOULDER2,
        .kind = TILE_BOULDER
    }
};

u8 GetTileId(const char *stringId)
{
    size_t len = sizeof(Tiles) / sizeof(TileData);
    for (size_t i = 0; i < len; i++)
        if (!strcmp(Tiles[i].id, stringId))
            return i;
    return 0;
}
Texture2D *GetTileTexture(u8 tileId)
{
    return Tiles[tileId].texture;
}
Texture2D *GetTileOutline(u8 tileId)
{
    return Tiles[tileId].outline;
}
TileKind GetTileKind(u8 tileId)
{
    return Tiles[tileId].kind;
}
u32 GetTileCost(u8 tileId)
{
    return Tiles[tileId].cost;
}
u32 GetTileSpace(u8 tileId)
{
    return Tiles[tileId].space;
}
i32 GetHappinessFactor(u8 tileId)
{
    return Tiles[tileId].happinessFactor;
}
i32 GetPowerFactor(u8 tileId)
{
    return Tiles[tileId].powerFactor;
}
const char *GetStringId(u8 tileId)
{
    return Tiles[tileId].id;
}
bool TileIsBuilding(u8 tileId)
{
    TileKind kind = GetTileKind(tileId);
    for (usize i = 0; i < BUILDINGS_LEN; i++)
        if (kind == Buildings[i])
            return true;
    return false;
}
f32 GetPerformanceFactor(u8 tileId)
{
    return Tiles[tileId].performanceFactor;
}
bool GetInternalHappinessBoost(u8 tileId)
{
    return Tiles[tileId].internalHappinessBoost;
}
char *GetTileName(u8 tileId)
{
    return Tiles[tileId].name;
}
char *GetTileComment(u8 tileId)
{
    return Tiles[tileId].comment;
}
