#include "logic/actions.h"

#include "logic/map.h"
#include "readonly/tiles.h"
#include "readonly/recipes.h"
#include "readonly/textures.h"

i32 currentAction = 0;

static HexCoord mergeFrom = { -100, -100 };

void UpdateActions(HexCoord mousePoint)
{
    if (currentAction == 3)
    {
        if (HexEqual(mergeFrom, mousePoint)) {
            mergeFrom = (HexCoord) { -100, -100 };
            return;
        } else if (HexEqual(mergeFrom, (HexCoord) { -100, -100 })) {
            mergeFrom = mousePoint;
            return;
        }
        const char * const RECIPE_RESULT = SearchOutput(
            GetStringId(GetTile(1, mergeFrom)),
            GetStringId(GetTile(1, mousePoint))
        );
        if (HexIsNeighbour(mergeFrom, mousePoint) && RECIPE_RESULT)
        {
            SetTile(1, mergeFrom, 0);
            SetTile(1, mousePoint, GetTileId(RECIPE_RESULT));
            mergeFrom = (HexCoord) { -100, -100 };
        }
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
