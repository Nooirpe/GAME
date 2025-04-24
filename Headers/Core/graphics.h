#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Systems/defs.h"
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
};

#endif // _GRAPHICS__H
