#include "logic/actions.h"

#include "logic/map.h"
#include "logic/state.h"
#include "readonly/tiles.h"
#include "readonly/recipes.h"
#include "readonly/textures.h"

i32 currentAction = 0;

static HexCoord mergeFrom = { -100, -100 };

static void Action1(HexCoord mousePoint)
{
    if (TileIsBuilding(GetTile(1, mousePoint)) && Iron >= DESTROY_BUILDING_COST) {
        SetTile(1, mousePoint, 0);
        Iron -= DESTROY_BUILDING_COST;
    }
}
static void Action2(HexCoord mousePoint)
{
    if (GetTileKind(GetTile(1, mousePoint)) == TILE_BOULDER && Iron >= DESTROY_BOULDER_COST) {
        SetTile(1, mousePoint, 0);
        Iron -= DESTROY_BOULDER_COST;
    }
}
static void Action3(HexCoord mousePoint)
{
    if (HexEqual(mergeFrom, mousePoint)) {
        mergeFrom = (HexCoord) { -100, -100 };
        return;
    } else if (HexEqual(mergeFrom, (HexCoord) { -100, -100 })) {
        mergeFrom = mousePoint;
        return;
    }
    MergeRecipe RECIPE_RESULT = SearchRecipe(
        GetStringId(GetTile(1, mergeFrom)),
        GetStringId(GetTile(1, mousePoint))
    );
    if (HexIsNeighbour(mergeFrom, mousePoint) && RECIPE_RESULT.result && RECIPE_RESULT.cost <= Iron)
    {
        SetTile(1, mergeFrom, 0);
        SetTile(1, mousePoint, GetTileId(RECIPE_RESULT.result));
        mergeFrom = (HexCoord) { -100, -100 };
        Iron -= RECIPE_RESULT.cost;
    }
}

void UpdateActions(HexCoord mousePoint)
{
    switch (currentAction)
    {
        case 1: Action1(mousePoint); break;
        case 2: Action2(mousePoint); break;
        case 3: Action3(mousePoint); break;
    }
}
void DrawActions(void)
{
    if (HexEqual(mergeFrom, (HexCoord) { -100, -100 }))
        return;
    Vector2 pos = CalculateTileScreenPos(mergeFrom);
    pos.y += TEXTURE_HIGHLIGHT_BLUE.height / 2;
    DrawTexture(TEXTURE_HIGHLIGHT_BLUE, pos.x, pos.y, WHITE);
}
HexCoord GetMergeFrom(void)
{
    return mergeFrom;
}
