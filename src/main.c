#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 20

#include "textures.h"
#include "map.h"
#include "tiles.h"
#include "cursor.h"
#include "guiwindow.h"

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const float TILE_RADIUS = 16.0f;

bool showBuildBox = false;

static RenderTexture2D Screen;

u8 currentTile = 0;

static Vector2 BuildWindowPosition = { 10, 10 };
static Vector2 BuildWindowSize = { 210, 310 + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT };
static bool BuildWindowMinimized = true;
static bool BuildWindowMoving = false;
static bool BuildWindowResizing = false;
static Vector2 BuildWindowScroll;

HexCoord GetMousePointed(void)
{
    const float px = GetMousePosition().x / 2.0f - MAP_ORIGIN_X;
    const float py = GetMousePosition().y / 2.0f - MAP_ORIGIN_Y;

    const float q = (px - 16.0f) / 24.0f;
    const float r_ = (py - 16.0f * q - 32.0f) / 32.0f;

    const float cx = q;
    const float cz = r_;
    const float cy = -cx - cz;

    int rx = roundf(cx);
    int ry = roundf(cy);
    int rz = roundf(cz);

    const float dx = fabsf(rx - cx);
    const float dy = fabsf(ry - cy);
    const float dz = fabsf(rz - cz);

    if (dx > dy && dx > dz)
        rx = -ry - rz;
    else if (dy > dz)
        ry = -rx - rz;
    else
        rz = -rx - ry;

    return (HexCoord) {
        .x = rx,
        .y = rz + (rx + (rx & 1)) / 2
    };
}

void DrawBuildContent(Vector2 position, __attribute__((unused)) Vector2 scroll)
{
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 10, 190, 40 }, "Biodome"))
        currentTile = GetTileId("biodome");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 60, 190, 40 }, "Apartaments"))
        currentTile = GetTileId("apartaments");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 110, 190, 40 }, "Drill"))
        currentTile = GetTileId("drill");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 160, 190, 40 }, "Lab"))
        currentTile = GetTileId("lab");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 210, 190, 40 }, "Factory"))
        currentTile = GetTileId("factory");
    if (GuiButton((Rectangle){ position.x + 10, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + 260, 190, 40 }, "Generator"))
        currentTile = GetTileId("generator");
}

void UpdateDrawFrame(void)
{
    HexCoord current = GetMousePointed();

    if (GetMouseY() < 670 && !showBuildBox)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            SetTile(0, current, currentTile);
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            SetTile(0, current, 0);
    }

    BeginTextureMode(Screen);
        ClearBackground((Color) { 0xCA, 0x70, 0x4E, 255 });
        RenderMap();
        RenderMouseCursor(current, currentTile);
    EndTextureMode();
    BeginDrawing();
        DrawTexturePro(
            Screen.texture,
            (Rectangle) { 0, 0, Screen.texture.width, -(f32)Screen.texture.height },
            (Rectangle) { 0, 0, 720, 720 },
            (Vector2) { 0 },
            0,
            WHITE
        );

       if (GuiButton((Rectangle){ 10, 670, 210, 40 }, "#0#BUILD")) showBuildBox = !showBuildBox;
       (GuiButton((Rectangle){ 230, 670, 210, 40 }, "#1#DESTROY"));
       (GuiButton((Rectangle){ 450, 670, 210, 40 }, "#2#STATISTICS"));
       (GuiButton((Rectangle){ 670, 670, 40, 40 }, "#3#"));
       GuiWindowFloating(&BuildWindowPosition, &BuildWindowSize, &BuildWindowMinimized, &BuildWindowMoving, &BuildWindowResizing, DrawBuildContent, (Vector2) { 0 }, &BuildWindowScroll, "#0#BUILD");
       // if (showBuildBox)
       // {
       //      Rectangle windowBounds = { 10, 350, 210, 310 };
       //
       //      GuiPanel(windowBounds, NULL);
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 10, 190, 40 }, "Biodome"))
       //          currentTile = GetTileId("biodome");
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 60, 190, 40 }, "Apartaments"))
       //          currentTile = GetTileId("apartaments");
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 110, 190, 40 }, "Drill"))
       //          currentTile = GetTileId("drill");
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 160, 190, 40 }, "Lab"))
       //          currentTile = GetTileId("lab");
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 210, 190, 40 }, "Factory"))
       //          currentTile = GetTileId("factory");
       //
       //      if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 260, 190, 40 }, "Generator"))
       //          currentTile = GetTileId("generator");
       // }
    EndDrawing();
}

int main(int argc, char **argv)
{
	InitWindow(720, 720, WINDOW_TITLE);
    InitTextures();

#if !defined(PLATFORM_WEB)
    GuiLoadStyle("resources/raygui_styles/amber/style_amber.rgs");
#endif

    Screen = LoadRenderTexture(360, 360);

    GenerateMars();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
	while (!WindowShouldClose())
        UpdateDrawFrame();
#endif

    UnloadTextures();
    UnloadRenderTexture(Screen);
	CloseWindow();

	return 0;
}
