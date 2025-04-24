#ifndef _SOUND__H
#define _SOUND__H

#include "../../src/include/SDL2/SDL_mixer.h"
#include <string>

class Sound
{
public:
    Sound();
    ~Sound();

    // Initialize the audio system
    bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);

    // Load and manage music
    Mix_Music *loadMusic(const char *path);
    void playMusic(Mix_Music *music, int loops = -1);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(int volume); // 0-128
    int getMusicVolume();

    // Load and manage sound effects
    Mix_Chunk *loadSound(const char *path);
    void playSound(Mix_Chunk *sound, bool enabled = true);

    // Audio settings
    void applyAudioSettings(int option, Mix_Music *music, bool &sfxEnabled);

    // Close audio system
    void close();

private:
    // Audio management
    bool initialized;
};

extern Sound soundSystem;

#endif // _SOUND__H