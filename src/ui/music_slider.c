#include "ui/music_slider.h"

#include "common.h"
#include "music.h"

static float volume = 1;

void UpdateDrawMusic(void)
{
    GuiSlider((Rectangle) { 2, 710, 100, 10 }, "", "Volume", &volume, 0, 1);
    SetVolume(volume);
}
