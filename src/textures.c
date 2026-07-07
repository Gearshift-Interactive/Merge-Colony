#include "textures.h"
#include "common.h"

Texture2D TEXTURE_ROCKS1;
Texture2D TEXTURE_ROCKS2;
Texture2D TEXTURE_ROCKS3;

Texture2D TEXTURE_BOULDER1;
Texture2D TEXTURE_BOULDER2;

Texture2D TEXTURE_HIGHLIGHT;
Texture2D TEXTURE_FACTORY;
Texture2D TEXTURE_APARTAMENT;
Texture2D TEXTURE_DRILL;
Texture2D TEXTURE_BIODOME;

Texture2D TEXTURE_FACTORY_OUTLINE;
Texture2D TEXTURE_APARTAMENT_OUTLINE;
Texture2D TEXTURE_DRILL_OUTLINE;
Texture2D TEXTURE_BIODOME_OUTLINE;

void InitTextures(void)
{
    TEXTURE_ROCKS1 = LoadTexture("resources/tiles/rocks1.png");
    TEXTURE_ROCKS2 = LoadTexture("resources/tiles/rocks2.png");
    TEXTURE_ROCKS3 = LoadTexture("resources/tiles/rocks3.png");

    TEXTURE_BOULDER1 = LoadTexture("resources/tiles/boulder1.png");
    TEXTURE_BOULDER2 = LoadTexture("resources/tiles/boulder2.png");

    TEXTURE_FACTORY    = LoadTexture("resources/tiles/factory.png");
    TEXTURE_APARTAMENT = LoadTexture("resources/tiles/apartament.png");
    TEXTURE_DRILL      = LoadTexture("resources/tiles/drill.png");
    TEXTURE_HIGHLIGHT  = LoadTexture("resources/tiles/template2.png");
    TEXTURE_BIODOME    = LoadTexture("resources/tiles/biodome.png");

    TEXTURE_APARTAMENT_OUTLINE = LoadTexture("resources/tiles/apartament_outline.png");
    TEXTURE_DRILL_OUTLINE      = LoadTexture("resources/tiles/drill_outline.png");
    TEXTURE_FACTORY_OUTLINE    = LoadTexture("resources/tiles/factory_outline.png");
    TEXTURE_BIODOME_OUTLINE    = LoadTexture("resources/tiles/biodome_outline.png");
}
void UnloadTextures(void)
{
    UnloadTexture(TEXTURE_ROCKS1);
    UnloadTexture(TEXTURE_ROCKS2);
    UnloadTexture(TEXTURE_ROCKS3);

    UnloadTexture(TEXTURE_BOULDER1);
    UnloadTexture(TEXTURE_BOULDER2);

    UnloadTexture(TEXTURE_FACTORY);
    UnloadTexture(TEXTURE_APARTAMENT);
    UnloadTexture(TEXTURE_DRILL);
    UnloadTexture(TEXTURE_HIGHLIGHT);
    UnloadTexture(TEXTURE_BIODOME);
}
