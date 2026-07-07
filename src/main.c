#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#include "textures.h"
#include "map.h"

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const u32 ORIGIN_X = 8;
const u32 ORIGIN_Y = 8;

const float TILE_RADIUS = 16.0f;

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
    if (IsKeyPressed(KEY_ONE))
        currentTile = 1;
    if (IsKeyPressed(KEY_TWO))
        currentTile = 2;
    if (IsKeyPressed(KEY_THREE))
        currentTile = 3;
    if (IsKeyPressed(KEY_FOUR))
        currentTile = 4;

    if (IsKeyPressed(KEY_ESCAPE))
        currentTile = 0;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        SetTile(current, currentTile);

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
            switch (tile)
            {
            case 1:
                DrawTexture(TEXTURE_APARTAMENT, screenPos.x, screenPos.y, WHITE);
                break;
            case 2:
                DrawTexture(TEXTURE_DRILL, screenPos.x, screenPos.y, WHITE);
                break;
            case 3:
                DrawTexture(TEXTURE_FACTORY, screenPos.x, screenPos.y, WHITE);
                break;
            case 4:
                DrawTexture(TEXTURE_BIODOME, screenPos.x, screenPos.y, WHITE);
                break;
            }
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
    EndDrawing();
}

int main(int argc, char **argv)
{
	InitWindow(720, 720, WINDOW_TITLE);
    InitTextures();

    Screen = LoadRenderTexture(360, 360);

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
