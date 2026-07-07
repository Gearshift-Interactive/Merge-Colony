#include "textures.h"
#include "common.h"

Texture2D TEXTURE_HIGHLIGHT;
Texture2D TEXTURE_FACTORY;
Texture2D TEXTURE_APARTAMENT;
Texture2D TEXTURE_DRILL;
Texture2D TEXTURE_BIODOME;

void InitTextures(void)
{
    TEXTURE_FACTORY    = LoadTexture("resources/tiles/factory.png");
    TEXTURE_APARTAMENT = LoadTexture("resources/tiles/apartament.png");
    TEXTURE_DRILL      = LoadTexture("resources/tiles/drill.png");
    TEXTURE_HIGHLIGHT  = LoadTexture("resources/tiles/template2.png");
    TEXTURE_BIODOME    = LoadTexture("resources/tiles/biodome.png");
}
void UnloadTextures(void)
{
    UnloadTexture(TEXTURE_FACTORY);
    UnloadTexture(TEXTURE_APARTAMENT);
    UnloadTexture(TEXTURE_DRILL);
    UnloadTexture(TEXTURE_HIGHLIGHT);
    UnloadTexture(TEXTURE_BIODOME);
}
