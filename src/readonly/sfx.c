#include "readonly/sfx.h"

Sound SFX_BUTTON;
Sound SFX_BUILD;
Sound SFX_DESTROY_BUILDING;
Sound SFX_DESTROY_BOULDER;
Sound SFX_PLAY;
Sound SFX_MERGE;

void InitSFX(void)
{
    SFX_BUTTON = LoadSound("resources/audio/button.wav");
    SFX_BUILD = LoadSound("resources/audio/build.wav");
    SFX_DESTROY_BUILDING = LoadSound("resources/audio/destroy_building.wav");
    SFX_DESTROY_BOULDER = LoadSound("resources/audio/destroy_boulder.wav");
    SFX_PLAY = LoadSound("resources/audio/play.wav");
    SFX_MERGE = LoadSound("resources/audio/merge.wav");
}
void UnloadSFX(void)
{
    UnloadSound(SFX_BUTTON);
    UnloadSound(SFX_BUILD);
    UnloadSound(SFX_DESTROY_BUILDING);
    UnloadSound(SFX_DESTROY_BOULDER);
    UnloadSound(SFX_PLAY);
    UnloadSound(SFX_MERGE);
}
