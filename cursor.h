#ifndef MOUSE_H
#define MOUSE_H
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"
#include "graphics.h"

struct Cursor
{

    SDL_Texture *texCursor1, *texCursor2;
    SDL_Rect rect;
    SDL_Rect point;

    bool in = 0;

    void createCursor(const Graphics &graphics)
    {
        texCursor1 = IMG_LoadTexture(graphics.renderer, "sdl_image\\cursor1.png");
        texCursor2 = IMG_LoadTexture(graphics.renderer, "sdl_image\\cursor2.png");
        rect.w = 40;
        rect.h = 40;
        point.w = 1;
        point.h = 1;
    }

    void update()
    {
        SDL_GetMouseState(&rect.x, &rect.y);
        point.x = rect.x;
        point.y = rect.y;
    }

    void draw(const Graphics &graphics)
    {
        if (in)
            SDL_RenderCopy(graphics.renderer, texCursor2, NULL, &rect);
        else
            SDL_RenderCopy(graphics.renderer, texCursor1, NULL, &rect);
    }
};

#endif
