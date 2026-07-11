#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#include "logic/map.h"
#include "logic/state.h"
#include "logic/map_updater.h"
#include "logic/actions.h"
#include "readonly/textures.h"
#include "readonly/tiles.h"
#include "readonly/sfx.h"
#include "ui/cursor.h"
#include "ui/interface.h"
#include "ui/mainmenu.h"
#include "ui/music_slider.h"
#include "music.h"

#include <time.h>


#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const float TILE_RADIUS = 16.0f;

bool showBuildBox = false;

static RenderTexture2D Screen;

u8 currentTile = 0;

static double sinceLastTick = 0;

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

void UpdateDrawFrame(void)
{
    UpdateMusic();

    switch (currentScreen)
    {
        case SCREEN_MENU: UpdateDrawMenu(); UpdateDrawMusic(); return;
        case SCREEN_CREDITS: UpdateDrawCredits(); UpdateDrawMusic(); return;
        case SCREEN_SEED: UpdateDrawSeed(); UpdateDrawMusic(); return;
        default: {}
    }

    HexCoord current = GetMousePointed();

    if (IsTileInMap(current) && !IsCursorOnGui(GetMousePosition()))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (!GetTile(1, current) && Copper >= GetTileCost(currentTile) && currentTile)
            {
                SetTile(1, current, currentTile);
                Copper -= GetTileCost(currentTile);
                PlaySound(SFX_BUILD);
            }
            else
                UpdateActions(current);
        }
    }

    sinceLastTick += GetFrameTime();
    if (sinceLastTick > 1)
    {
        sinceLastTick -= 1;
        UpdateMap();
    }

    BeginTextureMode(Screen);
        ClearBackground((Color) { 0xC8, 0x6D, 0x4D, 255 });
        RenderMap();
        DrawActions();
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
        UpdateDrawGui();
        UpdateDrawMusic();
    EndDrawing();
}

int main(void)
{
    srand(time(NULL));
	InitWindow(720, 720, WINDOW_TITLE);
    SetExitKey(KEY_NULL);
    InitTextures();
    InitGui(&currentTile);
    InitMusic();
    InitSFX();

#if !defined(PLATFORM_WEB)
    GuiLoadStyle("resources/raygui_styles/amber/style_amber.rgs");
#endif

    Screen = LoadRenderTexture(360, 360);

    InitMenu();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	while (!WindowShouldClose())
        UpdateDrawFrame();
#endif

    UnloadTextures();
    UnloadRenderTexture(Screen);
    UnloadSFX();
    UnloadMusic();
	CloseWindow();

	return 0;
}
