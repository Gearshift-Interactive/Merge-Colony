#include "ui/mainmenu.h"
#include "logic/map.h"
#include "logic/state.h"

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

static void UpdateStars(void)
{
    for (int i = 0; i < starCount; i++)
    {
        stars[i].pos.y += stars[i].speed;
        if (stars[i].pos.y > 720) ResetStar(i);
    }
}
static void RenderStars(void)
{
    for (int i = 0; i < starCount; i++)
    {
        Color c = Fade(WHITE, stars[i].alpha);
        DrawCircleV(stars[i].pos, stars[i].size, c);
    }
}

static char seedText[256] = "";
static bool seedEditMode = false;

void UpdateDrawMenu(void)
{
    UpdateStars();

    BeginDrawing();
    ClearBackground(BLACK);

    RenderStars();

    if (GuiButton((Rectangle){ 260, 300, 200, 50 }, "#20# PLAY"))
    {
        seedText[0] = '\0';
        seedEditMode = false;
        currentScreen = SCREEN_SEED;
    }

    if (GuiButton((Rectangle){ 260, 370, 200, 50 }, "#7# CREDITS"))
        currentScreen = SCREEN_CREDITS;

#if !defined(PLATFORM_WEB)
    if (GuiButton((Rectangle){ 260, 440, 200, 50 }, "#19# EXIT"))
    {
        exit(0);
    }
#endif

    EndDrawing();
}

void UpdateDrawCredits(void)
{
    UpdateStars();

    BeginDrawing();
    ClearBackground(BLACK);

    RenderStars();

    int y = 200;
    const char *text[] = {
        "Big thanks to these awesome peple that",
        "were involved in this game's development:",
        "Priklen - Lead Programmer & Artist",
        "koff - Programmer",
        "Marc - Composer & Sound designer",
        "Sai-Tess - Artist"
    };
    for (size_t i = 0; i < sizeof(text)/sizeof(text[0]); i++)
    {
        int tw = MeasureText(text[i], 20);
        DrawText(text[i], 360 - tw/2, y, 20, WHITE);
        y += 30;
    }

    if (GuiButton((Rectangle){ 260, 500, 200, 50 }, "#19# Back"))
        currentScreen = SCREEN_MENU;

    EndDrawing();
}

static u32 HashString(const char *s)
{
    u32 hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + (unsigned char)c;
    return hash;
}

void UpdateDrawSeed(void)
{
    UpdateStars();

    BeginDrawing();
    ClearBackground(BLACK);

    RenderStars();

    GuiLabel((Rectangle){ 260, 280, 140, 16 }, "Seed:");
    if (GuiTextBox((Rectangle){ 260, 300, 140, 50 }, seedText, sizeof(seedText), seedEditMode))
        seedEditMode = !seedEditMode;


    if (GuiButton((Rectangle){ 410, 300, 50, 50 }, "#22#"))
    {
        u32 rnd = (u32)rand();
        snprintf(seedText, sizeof(seedText), "%u", rnd);
        seedEditMode = false;
    }

    if (GuiButton((Rectangle){ 260, 370, 200, 50 }, "#20# PLAY"))
    {
        ResetState();
        u32 seed = (seedText[0] != '\0') ? HashString(seedText) : (u32)rand();
        GenerateMars(seed);
        currentScreen = SCREEN_MARS;
    }

    if (GuiButton((Rectangle){ 260, 440, 200, 50 }, "#19# BACK"))
        currentScreen = SCREEN_MENU;

    EndDrawing();
}
