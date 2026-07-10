#include "music.h"

#include "ui/mainmenu.h"

static Music mainMenuMusic;

static Music planetMusic[3] = { 0 };
static u8 currentSong = 0;

static GameScreen prev;

void InitMusic(void)
{
    InitAudioDevice();
    mainMenuMusic = LoadMusicStream("resources/audio/main_menu.wav");
    mainMenuMusic.looping = true;
    planetMusic[0] = LoadMusicStream("resources/audio/planet1.wav");
    planetMusic[0].looping = false;
    planetMusic[1] = LoadMusicStream("resources/audio/planet2.wav");
    planetMusic[1].looping = false;
    planetMusic[2] = LoadMusicStream("resources/audio/planet3.wav");
    planetMusic[2].looping = false;
    PlayMusicStream(mainMenuMusic);
}
static void UpdateNext(void)
{
    currentSong++;
    if (currentSong > 2)
        currentSong = 0;
}
void UpdateMusic(void)
{
    if (prev != currentScreen)
    {
        if (currentScreen == SCREEN_MARS)
        {
            StopMusicStream(mainMenuMusic);
            PlayMusicStream(planetMusic[currentSong]);
        }
        else if (prev == SCREEN_MARS)
        {
            StopMusicStream(planetMusic[currentSong]);
            PlayMusicStream(mainMenuMusic);
        }
    }
    if (currentScreen == SCREEN_MARS)
        UpdateMusicStream(planetMusic[currentSong]);
    else
        UpdateMusicStream(mainMenuMusic);
    if (!IsMusicStreamPlaying(planetMusic[currentSong]) && currentScreen == SCREEN_MARS)
    {
        UpdateNext();
        PlayMusicStream(planetMusic[currentSong]);
    }
    prev = currentScreen;
}
void UnloadMusic(void)
{
    UnloadMusicStream(mainMenuMusic);
    UnloadMusicStream(planetMusic[0]);
    UnloadMusicStream(planetMusic[1]);
    UnloadMusicStream(planetMusic[2]);
    CloseAudioDevice();
}
void SetVolume(float volume)
{
    if (currentScreen == SCREEN_MARS)
        SetMusicVolume(planetMusic[currentSong], volume);
    else
        SetMusicVolume(mainMenuMusic, volume);
}
