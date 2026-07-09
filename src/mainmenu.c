#include "mainmenu.h"
#include "map.h"
#include "state.h"

GameScreen currentScreen = SCREEN_MENU;

typedef struct {
    Vector2 pos;
    float speed;
    float size;
    float alpha;
} Star;

static Star stars[50];
static int starCount = 50;

static void ResetStar(int i)
{
    stars[i].pos.x = GetRandomValue(0, 720);
    stars[i].pos.y = 0;
    stars[i].speed = 0.5f + (float)GetRandomValue(5, 30) / 10.0f;
    stars[i].size  = 1.0f + (float)GetRandomValue(0, 25) / 10.0f;
    stars[i].alpha = 0.3f + (float)GetRandomValue(0, 70) / 100.0f;
}

void InitMenu(void)
{
    currentScreen = SCREEN_MENU;
    for (int i = 0; i < starCount; i++)
    {
        stars[i].pos.x = GetRandomValue(0, 720);
        stars[i].pos.y = GetRandomValue(0, 720);
        stars[i].speed = 0.5f + (float)GetRandomValue(5, 30) / 10.0f;
        stars[i].size  = 1.0f + (float)GetRandomValue(0, 25) / 10.0f;
        stars[i].alpha = 0.3f + (float)GetRandomValue(0, 70) / 100.0f;
    }
}

void UpdateDrawMenu(void)
{
    for (int i = 0; i < starCount; i++)
    {
        stars[i].pos.y += stars[i].speed;
        if (stars[i].pos.y > 720) ResetStar(i);
    }

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < starCount; i++)
    {
        Color c = Fade(WHITE, stars[i].alpha);
        DrawCircleV(stars[i].pos, stars[i].size, c);
    }

    if (GuiButton((Rectangle){ 260, 300, 200, 50 }, "game"))
    {
        GenerateMars();
        currentScreen = SCREEN_MARS;
    }

    if (GuiButton((Rectangle){ 260, 370, 200, 50 }, "credits"))
        currentScreen = SCREEN_CREDITS;

#if !defined(PLATFORM_WEB)
    if (GuiButton((Rectangle){ 260, 440, 200, 50 }, "#1#"))
    {
        exit(0);
    }
#endif

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
