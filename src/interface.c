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
    .size = { 210, 460 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static const WindowData *WINDOWS[] = {
    &BuildWindow, &DestroyWindow, &StatisticsWindow
};

static u8 *currentTile;

static void DrawBuildContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 }, "Biodome"))
        *currentTile = GetTileId("biodome");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40  }, "Apartaments"))
        *currentTile = GetTileId("apartaments");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 }, "Drill"))
        *currentTile = GetTileId("drill");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 160, 190, 40 }, "Lab"))
        *currentTile = GetTileId("lab");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 210, 190, 40 }, "Factory"))
        *currentTile = GetTileId("factory");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 260, 190, 40 }, "Generator"))
        *currentTile = GetTileId("generator");
}

static void DrawStatContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },  TextFormat("#1#               %d",
                                                                                                                            Tehos));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 },  TextFormat("#1# Population    %d",
                                                                                                                            Population));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 }, TextFormat("#1# Happiness     %d",
                                                                                                                            Happiness));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 160, 190, 40 }, TextFormat("#1# Water         %d",
                                                                                                                            Water));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 210, 190, 40 }, TextFormat("#1# Food          %d",
                                                                                                                            Food));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 260, 190, 40 }, TextFormat("#1# Electricity   %d",
                                                                                                                            Electricity));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 310, 190, 40 }, TextFormat("#1# Iron          %d",
                                                                                                                            Iron));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 360, 190, 40 }, TextFormat("#1# Copper        %d",
                                                                                                                            Copper));
    GuiLabel((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 410, 190, 40 }, TextFormat("#1# Uranium       %d",
                                                                                                                            Uranium));
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
