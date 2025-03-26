#ifndef _GAME__H
#define _GAME__H
#include "player.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_image.h"
#include "graphics.h"
#include "cursor.h"
#include <bits/stdc++.h>

using namespace std;
void intro(Graphics graphics)
{
    SDL_Texture *show = graphics.loadTexture("sdl_image\\Intro\\Intro 1.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(2780);

    SDL_DestroyTexture(show);
    show = graphics.loadTexture("sdl_image\\Intro\\Intro 2.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(2780);

    SDL_DestroyTexture(show);
    show = graphics.loadTexture("sdl_image\\Intro\\Intro 3.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(700);
    SDL_DestroyTexture(show);
}
void menu(SDL_Texture *mn, Graphics &graphics, Cursor &cursor, SDL_Event &e, int &count, bool &quit, bool &playSound, bool &ingame, int &options, int &level, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose)
{
    cursor.update();
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    int prevCount = count;
    if (count == 1)
    {
        if (cursor.point.x > 541 && cursor.point.x < 877)
        {
            if (cursor.point.y > 361 && cursor.point.y < 474)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 2.png");
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }

                /* if (SDL_PollEvent(&e))
                { */
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    count = 2;
                    if (prevCount != count)
                        return;
                }
                //}
            }
            else if (cursor.point.y > 511 && cursor.point.y < 630)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 3.png");
                // if (SDL_PollEvent(&e))
                //{
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    count = 3;
                }
                //}
            }
            else if (cursor.point.y > 653 && cursor.point.y < 743)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 4.png");
                // if (SDL_PollEvent(&e))
                //{
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    count = 4;
                }
                //}
            }
            else
            {
                cursor.in = 0;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 1.png");
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\Menu 1.png");
        }
    }
    if (count == 2)
    {
        if (cursor.point.y > 280 && cursor.point.y < 604)
        {
            if (cursor.point.x > 176 && cursor.point.x < 399)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level 1.png");
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }
                // if (SDL_PollEvent(&e))
                //{
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    for (int i = 0; i < 12; i++)
                    {
                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level 1.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }
                    mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                    graphics.prepareScene(mn);
                    graphics.presentScene();
                    SDL_DestroyTexture(mn);
                    ingame = 1;
                    level = 1;
                }
                //}
            }
            else if (cursor.point.x > 574 && cursor.point.x < 829)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level 2.png");
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }
                // if (SDL_PollEvent(&e))
                //{
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    for (int i = 0; i < 12; i++)
                    {
                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level 2.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }
                    mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                    graphics.prepareScene(mn);
                    graphics.presentScene();
                    SDL_DestroyTexture(mn);
                    ingame = 1;
                    level = 2;
                }
                //}
            }
            else if (cursor.point.x > 974 && cursor.point.x < 1226)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level 3.png");
                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }
                // if (SDL_PollEvent(&e))
                //{
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    for (int i = 0; i < 12; i++)
                    {
                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(mn);
                        mn = graphics.loadTexture("sdl_image\\Menu\\level 3.png");
                        graphics.prepareScene(mn);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }
                    mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                    graphics.prepareScene(mn);
                    graphics.presentScene();
                    SDL_DestroyTexture(mn);
                    ingame = 1;
                    level = 3;
                }
                //  }
            }
            else if (cursor.point.x > 76 && cursor.point.x < 138 && cursor.point.y > 122 && cursor.point.y < 192)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level.png");

                if (playSound)
                {
                    graphics.play(menuChoose);
                    playSound = false;
                }

                // if (SDL_PollEvent(&e))
                //  {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect);
                    count = 1;
                }
                //}
            }

            else
            {
                cursor.in = 0;
                playSound = true;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
            }

            if (currentKeyStates[SDL_SCANCODE_ESCAPE])
            {
                graphics.play(menuSelect);
                count = 1;
            }
        }
    }
    graphics.prepareImg(mn);
}
#endif