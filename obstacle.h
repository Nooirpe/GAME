#ifndef _OBSTACLE__H
#define _OBSTACLE__H
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL.h"
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL_image.h"
#include "graphics.h"
#include <bits/stdc++.h>
using namespace std;
struct Bat
{
    SDL_Rect rect;
    SDL_Texture *Bat;
    float dx, dy;
    float ax, ay, bx, by;
    float speed;

    void createBat(const Graphics &graphics)
    {
        Bat = IMG_LoadTexture(graphics.renderer, "Image\\Stage\\Bat.png");
        rect.h = BAT_SIZE;
        rect.w = BAT_SIZE;
    }
};
#endif