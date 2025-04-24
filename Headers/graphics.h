#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "C:\\C++\\GAME\\GAME\\src\\include\\SDL2\\SDL.h"
#include "C:\\C++\\GAME\\GAME\\src\\include\\SDL2\\SDL_image.h"
#include "defs.h"
#include "C:\\C++\\GAME\\GAME\\src\\include\\SDL2\\SDL_mixer.h"
#include <vector>

struct ScrollingBackground
{
    SDL_Texture *texture;    // Chứa ảnh nền
    int scrollingOffset = 0; // Vị trí ảnh nền
    int width, height;       // Kích thước ảnh nền lấy từ Query
    void setTexture(SDL_Texture *_texture);
    void scroll(int distance);
};

struct Graphics
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char *msg, const char *error);
    void init();
    void prepareImg(SDL_Texture *background);
    void prepareScene(SDL_Texture *background = nullptr);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();
    void render(const ScrollingBackground &background);
    Mix_Music *loadMusic(const char *path);
    void play(Mix_Music *gMusic);
    Mix_Chunk *loadSound(const char *path);
    void play(Mix_Chunk *sound, bool sfxEnabled = true);
};

#endif // _GRAPHICS__H
