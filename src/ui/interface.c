#include "ui/interface.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 20
#include "ui/guiwindow.h"

#include "ui/mainmenu.h"
#include "readonly/tiles.h"
#include "readonly/textures.h"
#include "logic/state.h"
#include "logic/map.h"
#include "logic/actions.h"

#include "string.h"

typedef struct {
    Vector2 position;
    Vector2 size;
    bool minimized;
    bool moving;
    bool resizing;
    Vector2 scroll;
} WindowData;

typedef struct {
    WindowData *data;
    char *title;
    void (*func)(Vector2, Vector2);
    bool closable;
    bool alwaysActive;
} Window;

static u8 inspected = 0;

static WindowData BuildWindow = {
    .position = { 10, 10 },
    .size = { 210, 230 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData DestroyWindow = {
    .position = { 10, 20 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .size = { 210, 225 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData StatisticsWindow = {
    .position = { 10, 40 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT * 3 },
    .size = { 210, 150 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData OverlayWindow = {
    .position = { 10, 30 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT * 2 },
    .size = { 210, 190 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
};
static WindowData InfoWindow = {
    .position = { 10, 50 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT * 4 },
    .size = { 210, 170 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
    .minimized = true
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
    u8 oldCurrentTile = *currentTile;
    i32 prexSelect = selected;
    GuiToggleGroup(
        (Rectangle){
            position.x + 10,
            position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10,
            190,
            40
        },
        "---\nBiodome\nHabitat\nDrill\nGenerator",
        &selected
    );
    if (selected != prexSelect)
        switch (selected)
        {
        case 0: *currentTile = 0; break;
        case 1: *currentTile = GetTileId("biodome"); break;
        case 2: *currentTile = GetTileId("apartaments"); break;
        case 3: *currentTile = GetTileId("drill"); break;
        case 4: *currentTile = GetTileId("generator"); break;
        }
    if (*currentTile != oldCurrentTile)
        currentAction = 0;
}

static void DrawStatContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    // GuiLabel(
    //     (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
    //     "#6#"
    // );
    // GuiLabel(
    //     (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
    //     TextFormat("%d", Tehos)
    // );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
        "#7# Population"
    );
    GuiLabel(
        (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 },
        TextFormat("%d/%d/%d", Population, Housing, Jobs)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 30, 190, 40 },
        (Happiness > 66) ? "#8# Happiness" : (Happiness > 33) ? "#9# Happiness" : "#10# Happiness"
    );
    GuiLabel(
        (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 30, 190, 40 },
        TextFormat("%d%%", Happiness)
    );
    // GuiLabel(
    //     (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 },
    //     "#11# Water"
    // );
    // GuiLabel(
    //     (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 },
    //     TextFormat("%d", Water)
    // );
    // GuiLabel(
    //     (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 80, 190, 40 },
    //     "#12# Food"
    // );
    // GuiLabel(
    //     (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 80, 190, 40 },
    //     TextFormat("%d", Food)
    // );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 },
        "#13# Electricity"
    );
    GuiLabel(
        (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 },
        TextFormat("%dkW/%dkW", ElectricityConsumed, ElectricityGenerated)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 },
        "#14# Iron"
    );
    GuiLabel(
        (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 },
        TextFormat("%d", Iron)
    );
    GuiLabel(
        (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 90, 190, 40 },
        "#15# Copper"
    );
    GuiLabel(
        (Rectangle){ position.x + 110, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 90, 190, 40 },
        TextFormat("%d", Copper)
    );
    // GuiLabel(
    //     (Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 150, 190, 40 },
    //     "#16# Uranium"
    // );
    // GuiLabel(
    //     (Rectangle){ position.x + 130, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 150, 190, 40 },
    //     TextFormat("%d", Uranium)
    // );
}
static void DrawToolsContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    i32 oldCurrentAction = currentAction;
    GuiToggleGroup(
        (Rectangle){
            position.x + 10,
            position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10,
            190,
            40
        },
        "---\n#1#Destroy building\n#1#Destroy boulder\n#25#Merge\n#18#Inspect",
        &currentAction
    );
    if (oldCurrentAction != currentAction) {
        *currentTile = 0;
        selected = 0;
    }
}
static void DrawOverlayContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    GuiToggleGroup(
        (Rectangle){
            position.x + 10,
            position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10,
            190,
            40
        },
        "---\n#15# Copper\n#14# Iron\n#8# Happiness",
        &CurrentOverlay
    );
}
static void DrawInfoContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    Vector2 oldpos = position;
    position.x += 10;
    position.y += 30 + TEXTURE_HEX.height;
    DrawTextureEx(TEXTURE_HEX, position, 0, 2, (Color) { 0xC8, 0x6D, 0x4D, 255 });
    position.y -= TEXTURE_HEX.height;
    DrawTextureEx(*GetTileTexture(inspected), position, 0, 2, WHITE);
    position.y += TEXTURE_HEX.height * 1.5f * 2.1f;
    GuiLabel((Rectangle) { position.x, position.y, 190, 20 }, GetTileName(inspected));
    if (GetTileComment(inspected))
    {
        position.y += 20;
        GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);
        GuiLabel((Rectangle) { position.x, position.y, 190, 40 }, GetTileComment(inspected));
        GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_NONE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_CENTER);
    }
    position = oldpos;
    position.y += 40;
    position.x += 20 + TEXTURE_HEX.width * 2;
    if (GetTileSpace(inspected))
    {
        const char *text;
        if (GetTileKind(inspected) == TILE_BUILDING_APARTAMENTS)
            text = TextFormat("#7#Beds: %d", GetTileSpace(inspected));
        else
            text = TextFormat("#7#Jobs: %d", GetTileSpace(inspected));
        GuiLabel((Rectangle) { position.x, position.y, 130, 16 }, text);
        position.y += 20;
    }
    if (GetHappinessFactor(inspected))
    {
        const char *text;
        if (GetHappinessFactor(inspected) > 0)
            text = TextFormat("#8#Happiness: +%d%%", GetHappinessFactor(inspected));
        else
            text = TextFormat("#10#Happiness: %d%%", GetHappinessFactor(inspected));
        GuiLabel((Rectangle) { position.x, position.y, 130, 16 }, text);
            position.y += 16;
        if (!GetInternalHappinessBoost(inspected))
            GuiLabel((Rectangle) { position.x, position.y, 130, 16 }, "    (for nearby)");
        else
            GuiLabel((Rectangle) { position.x, position.y, 130, 16 }, "    (for all)");
        position.y += 20;
    }
    if (GetPowerFactor(inspected))
    {
        const char *text;
        if (GetPowerFactor(inspected) > 0)
            text = TextFormat("#13#Generates: %dkW", GetPowerFactor(inspected));
        else
            text = TextFormat("#13#Consumes: %dkW", -GetPowerFactor(inspected));
        GuiLabel((Rectangle) { position.x, position.y, 130, 16 }, text);
        position.y += 20;
    }
}

void InitGui(u8 *currentTileVar)
{
    currentTile = currentTileVar;
}
static Window windows[] = {
    { .data=&BuildWindow, .title="#0#BUILD", .func=DrawBuildContent },
    { .data=&DestroyWindow, .title="#21#TOOLS", .func=DrawToolsContent },
    { .data=&OverlayWindow, .title="#18#OVERLAY", .func=DrawOverlayContent },
    { .data=&StatisticsWindow, .title="#2#STATISTICS", .func=DrawStatContent, .alwaysActive=true },
    { .data=&InfoWindow, .title="#23#INFO", .func=DrawInfoContent, .closable=true, .alwaysActive=true },
};
static const usize windowCount = sizeof(windows) / sizeof(windows[0]);
static void BringToFront(usize index)
{
    if (index == windowCount - 1)
        return;

    Window tmp = windows[index];

    memmove(
        &windows[index],
        &windows[index + 1],
        (windowCount - index - 1) * sizeof(windows[0])
    );

    windows[windowCount - 1] = tmp;
}
void UpdateDrawGui(void)
{
    if (GuiButton((Rectangle){ 700, 700, 20, 20 }, "#19#"))
        currentScreen = SCREEN_MENU;
    // (GuiButton((Rectangle){ 10, 670, 210, 40 }, "#0#BUILD"));
    // (GuiButton((Rectangle){ 230, 670, 210, 40 }, "#1#DESTROY"));
    // (GuiButton((Rectangle){ 450, 670, 210, 40 }, "#2#STATISTICS"));
    // (GuiButton((Rectangle){ 670, 670, 40, 40 }, "#3#"));
    // if (!InfoWindow.minimized)
    //     GuiWindowFloating(
    //         &InfoWindow.position,
    //         &InfoWindow.size,
    //         &InfoWindow.minimized,
    //         &InfoWindow.moving,
    //         &InfoWindow.resizing,
    //         DrawInfoContent,
    //         (Vector2) { 0 },
    //         &InfoWindow.scroll,
    //         "#23#INFO",
    //         true
    //     );
    // GuiWindowFloating(
    //     &StatisticsWindow.position,
    //     &StatisticsWindow.size,
    //     &StatisticsWindow.minimized,
    //     &StatisticsWindow.moving,
    //     &StatisticsWindow.resizing,
    //     DrawStatContent,
    //     (Vector2) { 0 },
    //     &StatisticsWindow.scroll,
    //     "#2#STATISTICS",
    //     false
    // );
    // GuiWindowFloating(
    //     &OverlayWindow.position,
    //     &OverlayWindow.size,
    //     &OverlayWindow.minimized,
    //     &OverlayWindow.moving,
    //     &OverlayWindow.resizing,
    //     DrawOverlayContent,
    //     (Vector2) { 0 },
    //     &OverlayWindow.scroll,
    //     "#18#OVERLAY",
    //     false
    // );
    // GuiWindowFloating(
    //     &DestroyWindow.position,
    //     &DestroyWindow.size,
    //     &DestroyWindow.minimized,
    //     &DestroyWindow.moving,
    //     &DestroyWindow.resizing,
    //     DrawToolsContent,
    //     (Vector2) { 0 },
    //     &DestroyWindow.scroll,
    //     "#21#TOOLS",
    //     false
    // );
    // GuiWindowFloating(
    //     &BuildWindow.position,
    //     &BuildWindow.size,
    //     &BuildWindow.minimized,
    //     &BuildWindow.moving,
    //     &BuildWindow.resizing,
    //     DrawBuildContent,
    //     (Vector2) { 0 },
    //     &BuildWindow.scroll,
    //     "#0#BUILD",
    //     false
    // );
    int activeIndex = -1;
    for (int i = windowCount - 1; i >= 0; --i)
    {
        if (windows[i].closable && windows[i].data->minimized)
            continue;
        if (IsCursorOnWindow(GetMousePosition(), &windows[i].data->position, &windows[i].data->size, &windows[i].data->minimized))
        {
            activeIndex = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                BringToFront(i);
                activeIndex = windowCount - 1;
            }
            break;
        }
    }
    for (usize i = 0; i < windowCount; ++i)
    {
        if (windows[i].closable && windows[i].data->minimized)
            continue;
        GuiWindowFloating(
            &windows[i].data->position,
            &windows[i].data->size,
            &windows[i].data->minimized,
            &windows[i].data->moving,
            &windows[i].data->resizing,
            windows[i].func,
            (Vector2) { 0 },
            &windows[i].data->scroll,
            windows[i].title,
            windows[i].closable,
            (int)i == activeIndex,
            windows[i].alwaysActive
        );
    }
    if (IsKeyPressed(KEY_Q))
    {
        selected = 0;
        *currentTile = 0;
        currentAction = 0;
    }
}
bool IsCursorOnGui(Vector2 cursorPos)
{
    size_t len = sizeof(windows) / sizeof(windows[0]);
    for (size_t i = 0; i < len; i++)
        if (IsCursorOnWindow(
            cursorPos,
            &windows[i].data->position,
            &windows[i].data->size,
            &windows[i].data->minimized
        ))
            return true;
    return false;
}
void SetInspectedTile(u8 tileId)
{
    inspected = tileId;
    InfoWindow.minimized = false;
}
