#ifndef _SOUND__H
#define _SOUND__H

#include "../../src/include/SDL2/SDL_mixer.h"
#include <string>

/**
 * @class Sound
 * @brief Handles audio playback and management
 */
class Sound
{
public:
    Sound();
    ~Sound();

    /**
     * @brief Initializes the audio subsystem
     */
    bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);

    /**
     * @brief Loads music file from disk
     */
    Mix_Music *loadMusic(const char *path);

    /**
     * @brief Plays loaded music
     */
    void playMusic(Mix_Music *music, int loops = -1);

    void stopMusic();

    void pauseMusic();

    void resumeMusic();

    void setMusicVolume(int volume); // 0-128

    int getMusicVolume();

    /**
     * @brief Loads sound effect from disk
     */
    Mix_Chunk *loadSound(const char *path);

    void playSound(Mix_Chunk *sound, bool enabled = true);

    /**
     * @brief Apply audio settings based on option
     */
    void applyAudioSettings(int option, bool &sfxEnabled);

    /**
     * @brief Closes audio subsystem
     */
    void close();

private:
    bool initialized;
};

#endif // _SOUND__H