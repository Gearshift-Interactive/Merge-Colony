#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const u32 ORIGIN_X = 8;
const u32 ORIGIN_Y = 8;

const float TILE_RADIUS = 16.0f;

static RenderTexture2D Screen;
static Texture2D BaseTile;
static Texture2D HighlightTile;

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
    BeginTextureMode(Screen);
        ClearBackground((Color) {
            .r = 202,
            .g = 112,
            .b = 78,
            .a = 255,
        });
        HexCoord current = GetMousePointed();
        for (size_t x = 0; x < 14; x++)
        for (size_t y = 0; y < 9; y++)
            if (HexEqual((HexCoord) {x, y}, current))
                DrawTexture(
                    HighlightTile,
                    /* x */ ORIGIN_X + BaseTile.width * 0.75f * x,
                    /* y */ ORIGIN_Y + BaseTile.height * y + ( (x % 2 == 0)
                        ? BaseTile.height / 2
                        : 0
                    ),
                    WHITE
                );
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

    Screen = LoadRenderTexture(360, 360);
    BaseTile = LoadTexture("resources/tiles/template.png");
    HighlightTile = LoadTexture("resources/tiles/template2.png");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
	while (!WindowShouldClose())
        UpdateDrawFrame();
#endif

    UnloadRenderTexture(Screen);
    UnloadTexture(BaseTile);
	CloseWindow();

	return 0;
}
