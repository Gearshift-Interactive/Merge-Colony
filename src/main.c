#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#include "textures.h"
#include "map.h"
#include "tiles.h"

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const u32 ORIGIN_X = 8;
const u32 ORIGIN_Y = 8;

const float TILE_RADIUS = 16.0f;

bool showBuildBox = false;

static RenderTexture2D Screen;

u8 currentTile = 0;

HexCoord GetMousePointed(void)
{
    const float px = GetMousePosition().x / 2.0f - ORIGIN_X;
    const float py = GetMousePosition().y / 2.0f - ORIGIN_Y;

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
    HexCoord current = GetMousePointed();

    if (GetMouseY() < 670 && !showBuildBox)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            SetTile(current, currentTile);
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            SetTile(current, 0);
    }

    BeginTextureMode(Screen);
        ClearBackground((Color) {
            .r = 0xFA,
            .g = 0x74,
            .b = 0x3E,
            .a = 255,
        });
        for (size_t x = 0; x < 14; x++)
        for (size_t y = 0; y < 9; y++)
        {
            const HexCoord coord = {x, y};
            const Vector2 screenPos = {
                ORIGIN_X + TEXTURE_HIGHLIGHT.width * 0.75f * x,
                ORIGIN_Y + TEXTURE_HIGHLIGHT.height * y + ( (x % 2 == 0)
                    ? TEXTURE_HIGHLIGHT.height / 2
                    : 0
                )
            };
            if (HexEqual(coord, current))
                DrawTexture(
                    TEXTURE_HIGHLIGHT,
                    screenPos.x,
                    screenPos.y,
                    WHITE
                );
            const u8 tile = GetTile(coord);
            if (tile)
                DrawTexture(
                    *GetTileTexture(tile),
                    screenPos.x,
                    screenPos.y,
                    WHITE
                );
        }
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

       if (GuiButton((Rectangle){ 10, 670, 320, 40 }, "#185#build")) showBuildBox = !showBuildBox;
       (GuiButton((Rectangle){ 340, 670, 320, 40 }, "#189#statistics"));
       (GuiButton((Rectangle){ 670, 670, 40, 40 }, "orbit"));
       if (showBuildBox)
       {
            Rectangle windowBounds = { 10, 350, 320, 310 };

            GuiPanel(windowBounds, NULL);

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 10, 300, 40 }, "Biodome"))
                currentTile = GetTileId("biodome");

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 60, 300, 40 }, "Apartaments"))
                currentTile = GetTileId("apartaments");

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 110, 300, 40 }, "Drill"))
                currentTile = GetTileId("drill");

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 160, 300, 40 }, "Lab"))
                currentTile = GetTileId("lab");

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 210, 300, 40 }, "Factory"))
                currentTile = GetTileId("factory");

            if (GuiButton((Rectangle){ windowBounds.x + 10, windowBounds.y + 260, 300, 40 }, "Generator"))
                currentTile = GetTileId("generator");
       }
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
