#define SDL_MAIN_HANDLED
#include <iostream>
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Surface *image1;
SDL_Surface *image2;
SDL_Surface *surface;
SDL_Window *window;

SDL_Event ev;
bool running = true;

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << SDL_GetError();
        return 1;
    }
    window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log(SDL_GetError());
        SDL_Quit();
        return 1;
    }
    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        SDL_Log(SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 90, 120));
    SDL_Surface *load = SDL_LoadBMP("test.bmp");
    SDL_Surface *image = SDL_ConvertSurface(load, surface->format, 0);
    if (!image)
    {
        // load failed
    }
    SDL_BlitSurface(image1, NULL, surface, NULL);
    SDL_Rect dest;
    dest.x = 100;
    dest.y = 50;
    dest.w = 370;
    dest.h = 240;
    SDL_BlitSurface(image2, NULL, surface, &dest);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
bool load()
{
    SDL_Surface *temp1, *temp2;
    temp1 = SDL_LoadBMP("test1.bmp");
    temp2 = SDL_LoadBMP("test2.bmp");
    if (!temp1 || !temp2)
    {
        SDL_Log(SDL_GetError());
        SDL_Quit();
        return false;
    }
    image1 = SDL_ConvertSurface(temp1, surface->format, 0);
    image2 = SDL_ConvertSurface(temp2, surface->format, 0);
    if (!image1 || !image2)
    {
        cout << SDL_GetError();
        return false;
    }
    return true;
}
