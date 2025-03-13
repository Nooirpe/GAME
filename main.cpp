#define SDL_MAIN_HANDLED
#include <bits/stdc++.h>
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_image.h"
#include "defs.h"
#include "graphics.h"
#include "cursor.h"
using namespace std;
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    Cursor cursor;
    cursor.createCursor(graphics);
    SDL_Texture *mn = graphics.loadTexture("sdl_image/Menu/Menu.png");
    SDL_Event event;
    int x, y;
    while (true)
    {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;

    return 0;
}
