#include "../../Headers/Systems/sound.h"
#include <iostream>

Sound soundSystem;

Sound::Sound() : initialized(false)
{
}

Sound::~Sound()
{
    if (initialized)
    {
        close();
    }
}

bool Sound::init(int frequency, Uint16 format, int channels, int chunksize)
{
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0)
    {
        std::cout << "Error: " << Mix_GetError() << std::endl;
        return false;
    }

    initialized = true;
    return true;
}

Mix_Music *Sound::loadMusic(const char *path)
{
    Mix_Music *music = Mix_LoadMUS(path);
    if (music == nullptr)
    {
        std::cout << "Error loading music: " << Mix_GetError() << std::endl;
    }
    return music;
}

void Sound::playMusic(Mix_Music *music, int loops)
{
    if (music == nullptr)
        return;

    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, loops);
    }
    else if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
}

void Sound::stopMusic()
{
    Mix_HaltMusic();
}

void Sound::pauseMusic()
{
    Mix_PauseMusic();
}

void Sound::resumeMusic()
{
    Mix_ResumeMusic();
}

void Sound::setMusicVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

int Sound::getMusicVolume()
{
    return Mix_VolumeMusic(-1);
}

Mix_Chunk *Sound::loadSound(const char *path)
{
    Mix_Chunk *chunk = Mix_LoadWAV(path);
    if (chunk == nullptr)
    {
        std::cout << "Error loading sound: " << Mix_GetError() << std::endl;
    }
    return chunk;
}

void Sound::playSound(Mix_Chunk *sound, bool enabled)
{
    if (enabled && sound != nullptr)
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}

void Sound::applyAudioSettings(int option, bool &sfxEnabled)
{

    // Setting 1: Music ON, SFX ON
    if (option == 1)
    {
        Mix_VolumeMusic(68); // 100% volume
        sfxEnabled = true;
    }
    // Setting 2/3: Music OFF, SFX ON
    else if (option == 3)
    {
        Mix_VolumeMusic(0); // Mute music
        sfxEnabled = true;
    }
    // Setting 4/5: Music ON, SFX OFF
    else if (option == 5)
    {
        Mix_VolumeMusic(68); // 100% volume
        sfxEnabled = false;
    }
    // Setting 6: Music OFF, SFX OFF
    else if (option == 6)
    {
        Mix_VolumeMusic(0); // Mute music
        sfxEnabled = false;
    }
}

void Sound::close()
{
    Mix_CloseAudio();
    initialized = false;
}