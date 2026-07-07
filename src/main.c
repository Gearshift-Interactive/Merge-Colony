#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

const u32 ORIGIN_X = 000;
const u32 ORIGIN_Y = 000;

static RenderTexture2D Screen;

static Texture2D BaseTile;

void UpdateDrawFrame(void)
{
    BeginTextureMode(Screen);
        ClearBackground(RAYWHITE);
        for (size_t x = 0; x < 10; x++)
            for (size_t y = 0; y < 10; y++)
                DrawTexture(
                    BaseTile,
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
