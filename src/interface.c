#include "interface.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 20
#include "guiwindow.h"

#include "tiles.h"
#include "state.h"

typedef struct {
    Vector2 position;
    Vector2 size;
    bool minimized;
    bool moving;
    bool resizing;
    Vector2 scroll;
} WindowData;

static WindowData BuildWindow = {
    .position = { 10, 10 },
    .size = { 210, 310 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData DestroyWindow = {
    .position = { 10, 20 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .size = { 210, 310 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData StatisticsWindow = {
    .position = { 10, 30 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT * 2 },
    .size = { 210, 230 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static const WindowData *WINDOWS[] = {
    &BuildWindow, &DestroyWindow, &StatisticsWindow
};

static u8 *currentTile;
static i32 selected;

static void DrawBuildContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 }, "Biodome"))
    //     *currentTile = GetTileId("biodome");
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40  }, "Apartaments"))
    //     *currentTile = GetTileId("apartaments");
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 }, "Drill"))
    //     *currentTile = GetTileId("drill");
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 160, 190, 40 }, "Lab"))
    //     *currentTile = GetTileId("lab");
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 210, 190, 40 }, "Factory"))
    //     *currentTile = GetTileId("factory");
    // if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 260, 190, 40 }, "Generator"))
    //     *currentTile = GetTileId("generator");
    i32 prexSelect = selected;
    GuiToggleGroup(
        (Rectangle){
            position.x + 10,
            position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10,
            190,
            40
        },
        "---\nBiodome\nApartaments\nDrill\nLab\nFactory\nGenerator",
        &selected
    );
    if (selected != prexSelect)
        switch (selected)
        {
        case 0: *currentTile = 0; break;
        case 1: *currentTile = GetTileId("biodome"); break;
        case 2: *currentTile = GetTileId("apartaments"); break;
        case 3: *currentTile = GetTileId("drill"); break;
        case 4: *currentTile = GetTileId("lab"); break;
        case 5: *currentTile = GetTileId("factory"); break;
        case 6: *currentTile = GetTileId("generator"); break;
        }
}

static void DrawStatContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
        "#6#"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
        TextFormat("%d", Tehos)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 30, 190, 40 },
        "#7# Population"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 30, 190, 40 },
        TextFormat("%d", Population)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 50, 190, 40 },
        "#8# Happiness"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 50, 190, 40 },
        TextFormat("%d%%", Happiness)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 80, 190, 40 },
        "#11# Water"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 80, 190, 40 },
        TextFormat("%d", Water)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 100, 190, 40 },
        "#12# Food"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 100, 190, 40 },
        TextFormat("%d", Food)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 120, 190, 40 },
        "#13# Electricity"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 120, 190, 40 },
        TextFormat("%d", Electricity)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 150, 190, 40 },
        "#14# Iron"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 150, 190, 40 },
        TextFormat("%d", Iron)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 170, 190, 40 },
        "#15# Copper"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 170, 190, 40 },
        TextFormat("%d", Copper)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 190, 190, 40 },
        "#16# Uranium"
    );
    GuiLabel(
        (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 190, 190, 40 },
        TextFormat("%d", Uranium)
    );
}

void InitGui(u8 *currentTileVar)
{
    currentTile = currentTileVar;
}
void UpdateDrawGui(void)
{
    // (GuiButton((Rectangle){ 10, 670, 210, 40 }, "#0#BUILD"));
    // (GuiButton((Rectangle){ 230, 670, 210, 40 }, "#1#DESTROY"));
    // (GuiButton((Rectangle){ 450, 670, 210, 40 }, "#2#STATISTICS"));
    // (GuiButton((Rectangle){ 670, 670, 40, 40 }, "#3#"));
    GuiWindowFloating(
        &StatisticsWindow.position,
        &StatisticsWindow.size,
        &StatisticsWindow.minimized,
        &StatisticsWindow.moving,
        &StatisticsWindow.resizing,
        DrawStatContent,
        (Vector2) { 0 },
        &StatisticsWindow.scroll,
        "#2#SATISTICS"
    );
    GuiWindowFloating(
        &DestroyWindow.position,
        &DestroyWindow.size,
        &DestroyWindow.minimized,
        &DestroyWindow.moving,
        &DestroyWindow.resizing,
        NULL,
        (Vector2) { 0 },
        &DestroyWindow.scroll,
        "#1#DESTROY"
    );
    GuiWindowFloating(
        &BuildWindow.position,
        &BuildWindow.size,
        &BuildWindow.minimized,
        &BuildWindow.moving,
        &BuildWindow.resizing,
        DrawBuildContent,
        (Vector2) { 0 },
        &BuildWindow.scroll,
        "#0#BUILD"
    );
    if (IsKeyPressed(KEY_Q))
    {
        selected = 0;
        *currentTile = 0;
    }
}
bool IsCursorOnGui(Vector2 cursorPos)
{
    size_t len = sizeof(WINDOWS) / sizeof(WINDOWS[0]);
    for (size_t i = 0; i < len; i++)
        if (IsCursorOnWindow(
            cursorPos,
            &WINDOWS[i]->position,
            &WINDOWS[i]->size,
            &WINDOWS[i]->minimized
        ))
            return true;
    return false;
}
