#include "common.h"

#if defined(PLATFORM_WEB)
#    include <emscripten/emscripten.h>
#endif

#define WINDOW_TITLE APP_NAME " v" APP_VERSION

void UpdateDrawFrame(void)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(APP_NAME, 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}

int main(int argc, char **argv)
{
	InitWindow(1280, 720, WINDOW_TITLE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
	while (!WindowShouldClose())
        UpdateDrawFrame();
#endif

	CloseWindow();

	return 0;
}
