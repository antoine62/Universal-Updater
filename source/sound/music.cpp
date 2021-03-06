

#include "music.hpp"
#include <vector>
#include "STDirectory.hpp"
#include <algorithm>
#include "random.hpp"

static Mix_Music* song;
static Mix_Music* settings;
static Mix_Music* chill;
static std::vector<std::string> songs;
static bool musicMutex = false;
static bool donePlaying = false;
static size_t currentSong = 0;
static u8 currentVolume = 0;




bool SDLH_Init_Chill(void)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return false;
    }
    const int mix_flags = MIX_INIT_MP3;
    if ((Mix_Init(mix_flags) & mix_flags) != mix_flags)
    {
        fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    chill = Mix_LoadMUS("romfs:/Music/Chill.mp3");

    return true;
}

bool SDLH_Init_Settings(void)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return false;
    }
    const int mix_flags = MIX_INIT_MP3;
    if ((Mix_Init(mix_flags) & mix_flags) != mix_flags)
    {
        fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    settings = Mix_LoadMUS("romfs:/Music/Settings.mp3");

    return true;
}

bool SDLH_Init_SD(void)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    const int mix_flags = MIX_INIT_MP3;
    if ((Mix_Init(mix_flags) & mix_flags) != mix_flags)
    {
        fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    if (io::exists("/Universal-Updater/Music/"))
    {
        STDirectory d("/Universal-Updater/Music/");
        if (d.good() && d.count() > 0)
        {
            for (size_t i = 0; i < d.count(); i++)
            {
                if (!d.folder(i))
                {
                    std::string songName = d.item(i);
                    if (songName.substr(songName.size() - 3, 3) == "mp3")
                    {
                        songs.push_back("/Universal-Updater/Music/" + songName);
                    }
                }
            }
        }
    }

    std::sort(songs.begin(), songs.end());

    HIDUSER_GetSoundVolume(&currentVolume);
    
    return true;
}

void SDLH_Exit(void)
{
    if (musicMutex)
    {
        musicMutex = false;
    }
    else
    {
        donePlaying = true;
    }
    while (!donePlaying) svcSleepThread(125000000); // wait for SDLH_Play to be done
    if (song)
    {
        Mix_FreeMusic(song);
    } else if (settings) 
    {
        Mix_FreeMusic(settings);
    } else if (chill) {
        Mix_FreeMusic(chill);
    }
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void Music_SD(void) // If Settings is set to `SD`.
{
    musicMutex = true;
    while (musicMutex)
    {
        HIDUSER_GetSoundVolume(&currentVolume);
        if (!Mix_PlayingMusic() || (currentVolume == 0 && songs.size() > 1))
        {
            if (song)
            {
                Mix_FreeMusic(song);
                song = nullptr;
            }
            {
                currentSong = randomNumbers() % songs.size();
            }
            song = Mix_LoadMUS(songs[currentSong].c_str());
            Mix_PlayMusic(song, 1);
        }
        if (currentVolume == 0)
        {
            Mix_PauseMusic();
        }
        while (currentVolume == 0 && musicMutex)
        {
            HIDUSER_GetSoundVolume(&currentVolume);
            svcSleepThread(250000000);
        }
        if (Mix_PausedMusic() && musicMutex)
        {
            Mix_ResumeMusic();
        }
        svcSleepThread(250000000);
    }
    donePlaying = true;
}



void Music_Chill(void)
{
    Mix_PlayMusic(chill, -1); //If Settings is set to `Chill`.
}

void Music_Settings(void)
{
    Mix_PlayMusic(settings, -1);    //If Settings is set to `Settings`.
}