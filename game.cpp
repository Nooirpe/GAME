#include "game.h"

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
void AudioSettings(int options, Mix_Music *music, bool &sfxEnabled)
{
    switch (options)
    {
    case 1: // setting 1
        Mix_ResumeMusic();
        Mix_VolumeMusic(68);
        sfxEnabled = true;
        break;
    case 3: // setting 3
        Mix_PauseMusic();
        sfxEnabled = true;
        break;
    case 5: // setting 4
        Mix_ResumeMusic();
        Mix_VolumeMusic(68);
        sfxEnabled = false;
        break;
    case 6: // setting 2
        Mix_PauseMusic();
        sfxEnabled = false;
        break;
    }
}
void menu(SDL_Texture *mn, Graphics &graphics, Cursor &cursor, SDL_Event &e, int &count, bool &quit, bool &playSound, bool &ingame, int &options, int &level, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose, bool &sfxEnabled, Mix_Music *massahMusic)
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
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }

                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        count = 2;
                        if (prevCount != count)
                            return;
                    }
                }
            }
            else if (cursor.point.y > 511 && cursor.point.y < 630)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 3.png");
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        count = 3;
                    }
                }
            }
            else if (cursor.point.y > 653 && cursor.point.y < 743)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\Menu 4.png");
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        count = 4;
                    }
                }
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
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        for (int i = 0; i < 12; i++)
                        {
                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);

                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level 1.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);
                        }
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareImg(mn);
                        graphics.presentScene();
                        SDL_DestroyTexture(mn);
                        ingame = 1;
                        level = 1;
                    }
                }
            }
            else if (cursor.point.x > 574 && cursor.point.x < 829)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level 2.png");
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        for (int i = 0; i < 12; i++)
                        {
                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);

                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level 2.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);
                        }
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareImg(mn);
                        graphics.presentScene();
                        SDL_DestroyTexture(mn);
                        ingame = 1;
                        level = 2;
                    }
                }
            }
            else if (cursor.point.x > 974 && cursor.point.x < 1226)
            {
                cursor.in = 1;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level 3.png");
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        for (int i = 0; i < 12; i++)
                        {
                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);

                            SDL_DestroyTexture(mn);
                            mn = graphics.loadTexture("sdl_image\\Menu\\level 3.png");
                            graphics.prepareImg(mn);
                            graphics.presentScene();
                            SDL_Delay(50);
                        }
                        mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
                        graphics.prepareImg(mn);
                        graphics.presentScene();
                        SDL_DestroyTexture(mn);
                        ingame = 1;
                        level = 3;
                    }
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\level.png");
            }
        }
        else if (cursor.point.x > 76 && cursor.point.x < 138 && cursor.point.y > 122 && cursor.point.y < 192)
        {
            cursor.in = 1;
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\level.png");

            if (playSound)
            {
                graphics.play(menuChoose, sfxEnabled);
                playSound = false;
            }

            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect, sfxEnabled);
                    count = 1;
                }
            }
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
            graphics.play(menuSelect, sfxEnabled);
            count = 1;
        }
    }
    if (count == 3)
    {
        if (options == 1)
        {
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\setting 1.png");
        }
        else if (options == 2 || options == 3)
        {
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\setting 3.png");
            options = 3;
        }
        else if (options == 4 || options == 5)
        {
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\setting 4.png");
            options = 5;
        }
        else if (options == 6)
        {
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\setting 2.png");
        }
        if (cursor.point.x > 790 && cursor.point.x < 826)
        {
            if (cursor.point.y > 438 && cursor.point.y < 475)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (options == 1)
                        {
                            options = 2;
                            AudioSettings(3, massahMusic, sfxEnabled);
                        }
                        else if (options == 3)
                        {
                            options = 1;
                            graphics.play(menuSelect, sfxEnabled);
                            AudioSettings(1, massahMusic, sfxEnabled);
                        }
                        else if (options == 6)
                        {
                            options = 4;
                            graphics.play(menuSelect, sfxEnabled);
                            AudioSettings(5, massahMusic, sfxEnabled);
                        }
                        else if (options == 5)
                        {
                            options = 6;
                            AudioSettings(6, massahMusic, sfxEnabled);
                        }
                    }
                }
            }
            else if (cursor.point.y > 516 && cursor.point.y < 551)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (options == 1)
                        {
                            options = 4;
                        }
                        else if (options == 5)
                        {
                            options = 1;
                            graphics.play(menuSelect, sfxEnabled);
                        }
                        else if (options == 6)
                        {
                            options = 2;
                            graphics.play(menuSelect, sfxEnabled);
                        }
                        else if (options == 3)
                        {
                            options = 6;
                        }
                    }
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
            }
        }
        else if (cursor.point.x > 390 && cursor.point.x < 440 && cursor.point.y > 339 && cursor.point.y < 371)
        {
            cursor.in = 1;
            if (playSound)
            {
                graphics.play(menuChoose, sfxEnabled);
                playSound = false;
            }
            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    graphics.play(menuSelect, sfxEnabled);
                    count = 1;
                }
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
        }
        if (currentKeyStates[SDL_SCANCODE_ESCAPE])
        {
            graphics.play(menuSelect, sfxEnabled);
            count = 1;
        }
    }
    if (count == 4)
    {
        if (cursor.point.y > 539 && cursor.point.y < 584)
        {
            if (cursor.point.x > 541 && cursor.point.x < 633)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\quit 2.png");
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        quit = true;
                    }
                }
            }
            else if (cursor.point.x > 806 && cursor.point.x < 900)
            {
                cursor.in = 1;
                if (playSound)
                {
                    graphics.play(menuChoose, sfxEnabled);
                    playSound = false;
                }
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\quit 3.png");
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        graphics.play(menuSelect, sfxEnabled);
                        count = 1;
                    }
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
                SDL_DestroyTexture(mn);
                mn = graphics.loadTexture("sdl_image\\Menu\\quit 1.png");
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
            SDL_DestroyTexture(mn);
            mn = graphics.loadTexture("sdl_image\\Menu\\quit 1.png");
        }
        if (currentKeyStates[SDL_SCANCODE_ESCAPE])
        {
            graphics.play(menuSelect, sfxEnabled);
            count = 1;
        }
    }
    graphics.prepareImg(mn);
    SDL_DestroyTexture(mn);
}
void drawhealth(Graphics &graphics, Player &player, SDL_Texture *mn)
{
    SDL_Texture *healthTexture = nullptr;
    if (player.health == 5)
    {
        healthTexture = graphics.loadTexture("sdl_image\\Things\\Health\\health 5.png");
    }
    else if (player.health == 4)
    {
        healthTexture = graphics.loadTexture("sdl_image\\Things\\Health\\health 4.png");
    }
    else if (player.health == 3)
    {
        healthTexture = graphics.loadTexture("sdl_image\\Things\\Health\\health 3.png");
    }
    else if (player.health == 2)
    {
        healthTexture = graphics.loadTexture("sdl_image\\Things\\Health\\health 2.png");
    }
    else if (player.health == 1)
    {
        healthTexture = graphics.loadTexture("sdl_image\\Things\\Health\\health 1.png");
    }

    if (healthTexture)
    {
        // render
        SDL_RenderCopy(graphics.renderer, healthTexture, NULL, NULL);
        SDL_DestroyTexture(healthTexture);
    }
}
void win(Graphics &graphics, Player &player)
{
    SDL_Texture *mn = graphics.loadTexture("sdl_image\\Things\\win.png");
    SDL_RenderClear(graphics.renderer);
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(2000);
    SDL_DestroyTexture(mn);
}
void death(Graphics &graphics, Player &player, SDL_Texture *mn, bool &onelevel)
{
    SDL_RenderClear(graphics.renderer);
    player.health--;
    if (player.health == 4)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\5.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\4.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 3)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\4.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\3.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 2)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\3.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\2.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 1)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\2.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\1.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 0)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\1.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("sdl_image\\Things\\Death\\0.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
}
void gameover(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame)
{
    SDL_DestroyTexture(mn);
    SDL_RenderClear(graphics.renderer);
    mn = graphics.loadTexture("sdl_image\\Things\\gameover.png");
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(1200);
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
    player.health = 0;
    ingame = 0;
}
void complete(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame)
{
    SDL_DestroyTexture(mn);
    SDL_RenderClear(graphics.renderer);
    mn = graphics.loadTexture("sdl_image\\Things\\complete.png");
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(2000);
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
    ingame = 0;
}
