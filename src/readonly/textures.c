#include "readonly/textures.h"
#include "common.h"

Texture2D TEXTURE_HEX;

Texture2D TEXTURE_ROCKS1;
Texture2D TEXTURE_ROCKS2;
Texture2D TEXTURE_ROCKS3;

Texture2D TEXTURE_COPPER1;
Texture2D TEXTURE_COPPER2;

Texture2D TEXTURE_IRON1;
Texture2D TEXTURE_IRON2;

Texture2D TEXTURE_MOUNTAIN11;
Texture2D TEXTURE_MOUNTAIN12;
Texture2D TEXTURE_MOUNTAIN13;
Texture2D TEXTURE_MOUNTAIN21;
Texture2D TEXTURE_MOUNTAIN22;
Texture2D TEXTURE_MOUNTAIN23;
Texture2D TEXTURE_MOUNTAIN31;
Texture2D TEXTURE_MOUNTAIN32;
Texture2D TEXTURE_MOUNTAIN33;

Texture2D TEXTURE_BOULDER1;
Texture2D TEXTURE_BOULDER2;

Texture2D TEXTURE_HIGHLIGHT;
Texture2D TEXTURE_HIGHLIGHT_GREEN;
Texture2D TEXTURE_HIGHLIGHT_BLUE;
Texture2D TEXTURE_CROSS;

Texture2D TEXTURE_FACTORY;
Texture2D TEXTURE_APARTAMENT;
Texture2D TEXTURE_APARTAMENTL2;
Texture2D TEXTURE_APARTAMENTL3;
Texture2D TEXTURE_DRILL;
Texture2D TEXTURE_BIODOME;
Texture2D TEXTURE_LAB;
Texture2D TEXTURE_GENERATOR;

Texture2D TEXTURE_FACTORY_OUTLINE;
Texture2D TEXTURE_APARTAMENT_OUTLINE;
Texture2D TEXTURE_DRILL_OUTLINE;
Texture2D TEXTURE_BIODOME_OUTLINE;
Texture2D TEXTURE_LAB_OUTLINE;
Texture2D TEXTURE_GENERATOR_OUTLINE;

void InitTextures(void)
{
    TEXTURE_HEX = LoadTexture("resources/tiles/hex.png");

    TEXTURE_ROCKS1 = LoadTexture("resources/tiles/rocks1.png");
    TEXTURE_ROCKS2 = LoadTexture("resources/tiles/rocks2.png");
    TEXTURE_ROCKS3 = LoadTexture("resources/tiles/rocks3.png");

    TEXTURE_COPPER1 = LoadTexture("resources/tiles/copper1.png");
    TEXTURE_COPPER2 = LoadTexture("resources/tiles/copper2.png");

    TEXTURE_IRON1 = LoadTexture("resources/tiles/iron1.png");
    TEXTURE_IRON2 = LoadTexture("resources/tiles/iron2.png");

    TEXTURE_MOUNTAIN11 = LoadTexture("resources/tiles/mountain1-1.png");
    TEXTURE_MOUNTAIN12 = LoadTexture("resources/tiles/mountain1-2.png");
    TEXTURE_MOUNTAIN13 = LoadTexture("resources/tiles/mountain1-3.png");
    TEXTURE_MOUNTAIN21 = LoadTexture("resources/tiles/mountain2-1.png");
    TEXTURE_MOUNTAIN22 = LoadTexture("resources/tiles/mountain2-2.png");
    TEXTURE_MOUNTAIN23 = LoadTexture("resources/tiles/mountain2-3.png");
    TEXTURE_MOUNTAIN31 = LoadTexture("resources/tiles/mountain3-1.png");
    TEXTURE_MOUNTAIN32 = LoadTexture("resources/tiles/mountain3-2.png");
    TEXTURE_MOUNTAIN33 = LoadTexture("resources/tiles/mountain3-3.png");

    TEXTURE_BOULDER1 = LoadTexture("resources/tiles/boulder1.png");
    TEXTURE_BOULDER2 = LoadTexture("resources/tiles/boulder2.png");

    TEXTURE_HIGHLIGHT       = LoadTexture("resources/tiles/template2.png");
    TEXTURE_HIGHLIGHT_GREEN = LoadTexture("resources/tiles/highlight_green.png");
    TEXTURE_HIGHLIGHT_BLUE  = LoadTexture("resources/tiles/highlight_blue.png");
    TEXTURE_CROSS           = LoadTexture("resources/tiles/coross.png");

    TEXTURE_FACTORY      = LoadTexture("resources/tiles/factory.png");
    TEXTURE_APARTAMENT   = LoadTexture("resources/tiles/apartament.png");
    TEXTURE_APARTAMENTL2 = LoadTexture("resources/tiles/apartament_2.png");
    TEXTURE_APARTAMENTL3 = LoadTexture("resources/tiles/apartament_3.png");
    TEXTURE_DRILL        = LoadTexture("resources/tiles/drill.png");
    TEXTURE_BIODOME      = LoadTexture("resources/tiles/biodome.png");
    TEXTURE_LAB          = LoadTexture("resources/tiles/laboratory.png");
    TEXTURE_GENERATOR    = LoadTexture("resources/tiles/generator.png");

    TEXTURE_APARTAMENT_OUTLINE = LoadTexture("resources/tiles/apartament_outline.png");
    TEXTURE_DRILL_OUTLINE      = LoadTexture("resources/tiles/drill_outline.png");
    TEXTURE_FACTORY_OUTLINE    = LoadTexture("resources/tiles/factory_outline.png");
    TEXTURE_BIODOME_OUTLINE    = LoadTexture("resources/tiles/biodome_outline.png");
    TEXTURE_LAB_OUTLINE        = LoadTexture("resources/tiles/laboratory_outline.png");
    TEXTURE_GENERATOR_OUTLINE  = LoadTexture("resources/tiles/generator_outline.png");
}
void UnloadTextures(void)
{
    UnloadTexture(TEXTURE_HEX);

    UnloadTexture(TEXTURE_ROCKS1);
    UnloadTexture(TEXTURE_ROCKS2);
    UnloadTexture(TEXTURE_ROCKS3);

    UnloadTexture(TEXTURE_COPPER1);
    UnloadTexture(TEXTURE_COPPER2);

    UnloadTexture(TEXTURE_IRON1);
    UnloadTexture(TEXTURE_IRON2);

    UnloadTexture(TEXTURE_MOUNTAIN11);
    UnloadTexture(TEXTURE_MOUNTAIN12);
    UnloadTexture(TEXTURE_MOUNTAIN13);
    UnloadTexture(TEXTURE_MOUNTAIN21);
    UnloadTexture(TEXTURE_MOUNTAIN22);
    UnloadTexture(TEXTURE_MOUNTAIN23);
    UnloadTexture(TEXTURE_MOUNTAIN31);
    UnloadTexture(TEXTURE_MOUNTAIN32);
    UnloadTexture(TEXTURE_MOUNTAIN33);

    UnloadTexture(TEXTURE_BOULDER1);
    UnloadTexture(TEXTURE_BOULDER2);

    UnloadTexture(TEXTURE_HIGHLIGHT);
    UnloadTexture(TEXTURE_HIGHLIGHT_GREEN);
    UnloadTexture(TEXTURE_HIGHLIGHT_BLUE);
    UnloadTexture(TEXTURE_CROSS);

    UnloadTexture(TEXTURE_FACTORY);
    UnloadTexture(TEXTURE_APARTAMENT);
    UnloadTexture(TEXTURE_APARTAMENTL2);
    UnloadTexture(TEXTURE_APARTAMENTL3);
    UnloadTexture(TEXTURE_DRILL);
    UnloadTexture(TEXTURE_BIODOME);
    UnloadTexture(TEXTURE_LAB);
    UnloadTexture(TEXTURE_GENERATOR);

    UnloadTexture(TEXTURE_FACTORY_OUTLINE);
    UnloadTexture(TEXTURE_APARTAMENT_OUTLINE);
    UnloadTexture(TEXTURE_DRILL_OUTLINE);
    UnloadTexture(TEXTURE_BIODOME_OUTLINE);
    UnloadTexture(TEXTURE_LAB_OUTLINE);
    UnloadTexture(TEXTURE_GENERATOR_OUTLINE);
}
