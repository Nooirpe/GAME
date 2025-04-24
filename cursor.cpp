#include "cursor.h"
#include "graphics.h"

void Cursor::createCursor(const Graphics &graphics)
{
    texCursor1 = IMG_LoadTexture(graphics.renderer, "sdl_image\\cursor 1.png");
    texCursor2 = IMG_LoadTexture(graphics.renderer, "sdl_image\\cursor 2.png");
    rect.w = 60;
    rect.h = 60;
    point.w = 1;
    point.h = 1;
}

void Cursor::update()
{
    SDL_GetMouseState(&rect.x, &rect.y);
    point.x = rect.x;
    point.y = rect.y;
}

void Cursor::draw(const Graphics &graphics)
{
    if (in)
        SDL_RenderCopy(graphics.renderer, texCursor2, NULL, &rect);
    else
        SDL_RenderCopy(graphics.renderer, texCursor1, NULL, &rect);
}