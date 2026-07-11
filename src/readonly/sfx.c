#include "readonly/sfx.h"

Sound SFX_BUTTON;
Sound SFX_BUILD;
Sound SFX_DESTROY_BUILDING;
Sound SFX_DESTROY_BOULDER;
Sound SFX_PLAY;
Sound SFX_MERGE;

void InitSFX(void)
{
    SFX_BUTTON = LoadSound("resources/audio/button.ogg");
    SFX_BUILD = LoadSound("resources/audio/build.ogg");
    SFX_DESTROY_BUILDING = LoadSound("resources/audio/destroy_building.ogg");
    SFX_DESTROY_BOULDER = LoadSound("resources/audio/destroy_boulder.ogg");
    SFX_PLAY = LoadSound("resources/audio/play.ogg");
    SFX_MERGE = LoadSound("resources/audio/merge.ogg");
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
