#pragma once

#include "common.h"

typedef enum {
    SCREEN_MENU,
    SCREEN_MARS,
    SCREEN_CREDITS
} GameScreen;

extern GameScreen currentScreen;

void InitMenu(void);
void UpdateDrawMenu(void);
void UpdateDrawCredits(void);
