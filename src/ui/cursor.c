#include "ui/cursor.h"

#include "logic/map.h"
#include "logic/map_updater.h"
#include "logic/state.h"
#include "logic/actions.h"
#include "readonly/textures.h"
#include "readonly/tiles.h"
#include "readonly/recipes.h"
#include "ui/interface.h"
#include "raymath.h"

const double CURSOR_SPEED = 12.0f;
static Vector2 currentCursorPos = { 0 };
static Vector2 targetCursorPos  = { 0 };

static void RenderBuildingCursor(HexCoord tileSelected, u8 currentBuilding)
{
    if (GetTile(1, tileSelected))
        DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
    else
    {
        DrawTexture(*GetTileOutline(currentBuilding), currentCursorPos.x, currentCursorPos.y, WHITE);
        u32 cost = GetTileCost(currentBuilding);
        Color color = (Copper >= cost) ? RAYWHITE : RED;
        const char *text = TextFormat("%d", cost);
        DrawText(text, currentCursorPos.x + 16, currentCursorPos.y + 4, 8, color);
        GuiDrawIcon(15, currentCursorPos.x, currentCursorPos.y, 1, color);
        return;
    }
}
static void RenderMergeActionCursor(HexCoord tileSelected)
{
    Texture2D *TEXTURE = NULL;
    if (HexEqual(GetMergeFrom(), (HexCoord) { -100, -100 }))
    {
        if (TileIsBuilding(GetTile(1, tileSelected)))
            TEXTURE = &TEXTURE_HIGHLIGHT_GREEN;
        else
            TEXTURE = &TEXTURE_CROSS;
    }
    else
    {
        MergeRecipe recipe = SearchRecipe(
            GetStringId(GetTile(1, GetMergeFrom())),
            GetStringId(GetTile(1, tileSelected))
        );
        Color textColor = { 0 };
        if (recipe.result && HexIsNeighbour(GetMergeFrom(), tileSelected) && recipe.cost <= Iron)
        {
            textColor = RAYWHITE;
            TEXTURE = &TEXTURE_HIGHLIGHT_GREEN;
        } else {
            textColor = RED;
            TEXTURE = &TEXTURE_CROSS;
        }
        if (recipe.result && !HexEqual(tileSelected, GetMergeFrom()))
        {
            const char *text = TextFormat("%d", recipe.cost);
            DrawText(text, currentCursorPos.x + 16, currentCursorPos.y + 4, 8, textColor);
            GuiDrawIcon(14, currentCursorPos.x, currentCursorPos.y, 1, textColor);
        }
    }

    if (TEXTURE)
    {
        if (TEXTURE == &TEXTURE_CROSS)
            DrawTexture(*TEXTURE, currentCursorPos.x, currentCursorPos.y, WHITE);
        else
            DrawTexture(*TEXTURE, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);
    }
}
static void RenderDestroyBuildingCursor(HexCoord tileSelected)
{
    if (!TileIsBuilding(GetTile(1, tileSelected)))
    {
        DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
        return;
    }
    Color color = { 0 };
    if (Iron >= DESTROY_BUILDING_COST)
    {
        DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);
        color = RAYWHITE;
    }
    else
    {
        DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
        color = RED;
    }
    const char *text = TextFormat("%d", DESTROY_BUILDING_COST);
    DrawText(text, currentCursorPos.x + 16, currentCursorPos.y + 4, GuiGetFont().baseSize, color);
    GuiDrawIcon(14, currentCursorPos.x, currentCursorPos.y, 1, color);
}
static void RenderDestroyBoulderCursor(HexCoord tileSelected)
{
    if (GetTileKind(GetTile(1, tileSelected)) != TILE_BOULDER)
    {
        DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
        return;
    }
    Color color = { 0 };
    if (Iron >= DESTROY_BOULDER_COST)
    {
        DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);
        color = RAYWHITE;
    }
    else
    {
        DrawTexture(TEXTURE_CROSS, currentCursorPos.x, currentCursorPos.y, WHITE);
        color = RED;
    }
    const char *text = TextFormat("%d", DESTROY_BOULDER_COST);
    DrawText(text, currentCursorPos.x + 16, currentCursorPos.y + 4, GuiGetFont().baseSize, color);
    GuiDrawIcon(14, currentCursorPos.x, currentCursorPos.y, 1, color);
}
static void RenderInspectActionCursor(HexCoord tileSelected)
{
    if (!GetTile(1, tileSelected))
        return;
    DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);
    GuiDrawIcon(18, currentCursorPos.x + 8, currentCursorPos.y + 25, 1, RAYWHITE);
}
static void RenderActionCursor(HexCoord tileSelected)
{
    switch (currentAction)
    {
        case 1: RenderDestroyBuildingCursor(tileSelected); break;
        case 2: RenderDestroyBoulderCursor(tileSelected); break;
        case 3: RenderMergeActionCursor(tileSelected); break;
        case 4: RenderInspectActionCursor(tileSelected); break;
    }
}

void RenderMouseCursor(HexCoord tileSelected, u8 currentBuilding)
{
    if (!IsTileInMap(tileSelected) || IsCursorOnGui(GetMousePosition())) return;

    Vector2 tileCoord = CalculateTileScreenPos(tileSelected);
    targetCursorPos = tileCoord;
    float dt = GetFrameTime();
    currentCursorPos.x += (targetCursorPos.x - currentCursorPos.x) * CURSOR_SPEED * dt;
    currentCursorPos.y += (targetCursorPos.y - currentCursorPos.y) * CURSOR_SPEED * dt;

    if (currentBuilding) {
        RenderBuildingCursor(tileSelected, currentBuilding);
        return;
    }
    else if (currentAction) {
        RenderActionCursor(tileSelected);
        return;
    }
    else
        DrawTexture(TEXTURE_HIGHLIGHT, currentCursorPos.x, currentCursorPos.y + TEXTURE_HIGHLIGHT.height * 0.5f, WHITE);

    if (!CurrentOverlay)
    {
        GuiDisableTooltip();
        return;
    }

    u8 data = 0;
    i32 happ = 0;
    switch (CurrentOverlay)
    {
        // case 1:
        //     data = GetWater(tileSelected);
        //     break;
        case 1:
            data = GetCopper(tileSelected);
            break;
        case 2:
            data = GetIron(tileSelected);
            break;
        case 3:
            happ = CheckHappiness(tileSelected);
            break;
    }
    if (data)
    {
        const char *text = TextFormat("%.2f%%", data / 255.0f * 100);
        DrawText(text, currentCursorPos.x, currentCursorPos.y, GuiGetFont().baseSize, RAYWHITE);
    }
    else if (happ)
    {
        const char *text = TextFormat("%d%%", (happ < 0) ? 0 : (happ > 100) ? 100 : happ);
        DrawText(text, currentCursorPos.x + 5, currentCursorPos.y, GuiGetFont().baseSize, RAYWHITE);
    }
}
