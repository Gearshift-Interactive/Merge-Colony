#include "mainmenu.h"
#include "map.h"
#include "state.h"

GameScreen currentScreen = SCREEN_MENU;

void InitMenu(void)
{
    currentScreen = SCREEN_MENU;
}

void UpdateDrawMenu(void)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (GuiButton((Rectangle){ 260, 300, 200, 50 }, "game"))
    {
        GenerateMars();
        currentScreen = SCREEN_MARS;
    }

    if (GuiButton((Rectangle){ 260, 370, 200, 50 }, "credits"))
        currentScreen = SCREEN_CREDITS;

    EndDrawing();
}

void UpdateDrawCredits(void)
{
    BeginDrawing();
    ClearBackground(BLACK);

    int y = 200;
    const char *names[] = {
        "Grand CEO Gigoretto",
        "koff",
        "Marc",
        "SaiTess"
    };
    for (size_t i = 0; i < sizeof(names)/sizeof(names[0]); i++)
    {
        int tw = MeasureText(names[i], 20);
        DrawText(names[i], 360 - tw/2, y, 20, WHITE);
        y += 30;
    }

    if (GuiButton((Rectangle){ 260, 500, 200, 50 }, "back"))
        currentScreen = SCREEN_MENU;

    EndDrawing();
}
