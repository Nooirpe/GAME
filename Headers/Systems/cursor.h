#ifndef MOUSE_H
#define MOUSE_H
#include "../../src/include/SDL2/SDL.h"
#include "../Core/graphics.h"

struct Cursor
{
    SDL_Texture *texCursor1, *texCursor2;
    SDL_Rect rect;
    SDL_Rect point;

    bool in = 0;

    void createCursor(const Graphics &graphics);
    void update();
    void draw(const Graphics &graphics);
};

#endif
