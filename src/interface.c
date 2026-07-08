#include "interface.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 20
#include "guiwindow.h"

#include "tiles.h"

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

static u8 *currentTile;

static void DrawBuildContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 }, "Biodome"))
        *currentTile = GetTileId("biodome");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 }, "Apartaments"))
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
}
bool IsCursorOnGui(Vector2 cursorPos)
{
    return IsCursorOnWindow(cursorPos, &BuildWindow.position, &BuildWindow.size, &BuildWindow.minimized);
}
