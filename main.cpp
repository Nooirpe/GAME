#define SDL_MAIN_HANDLED
#include <bits/stdc++.h>
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_image.h"
#include "defs.h"
#include "graphics.h"
#include "cursor.h"
#include "player.h"
#include "animation.h"
#include "game.h"
#include "obstacle.h"
#include "stage.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_mixer.h"
using namespace std;
Mix_Music *massahMusic = nullptr;
int main()
{
    Graphics graphics;
    graphics.init();
    Cursor cursor;
    cursor.createCursor(graphics);
    // intro(graphics);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Error: " << Mix_GetError() << endl;
    }
    massahMusic = Mix_LoadMUS("Sound\\Massah.mp3");
    if (massahMusic == nullptr)
    {
        cout << "Error: " << Mix_GetError() << endl;
    }
    else
    {
        Mix_PlayMusic(massahMusic, -1);
        Mix_VolumeMusic(68);
    }
    Mix_Chunk *menuSelect = graphics.loadSound("Sound\\sfx\\menuselect.wav");
    Mix_Chunk *menuChoose = graphics.loadSound("Sound\\sfx\\menuchoose.wav");

    Player player(graphics.renderer);
    SDL_Texture *mn = graphics.loadTexture("sdl_image\\Menu\\Menu 1.png");
    SDL_Texture *mg;

    bool quit = false;
    int countmenu = 1;
    int options = 1;
    int level = 0;
    bool ingame = false; // vao game chua
    bool end = 0;
    bool playSound = true;
    bool playerDying = false;
    bool playerWinning = false;
    bool onemenu = true;    // Tranh lap menu
    bool onelevel = true;   // Tranh lap level
    bool sfxEnabled = true; // check sfx
    SDL_Event e;
    bool keyStates[SDL_NUM_SCANCODES] = {false}; // Dò key states
    Uint32 lastTime = SDL_GetTicks();
    Uint32 stateChangeTime = 0;
    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
        if (!ingame)
        {
            if (onemenu)
            {
                cursor.in = 0;
                countmenu = 1;
                playSound = true;
                ingame = false;
                level = 0;
                onemenu = false;
            }
            SDL_RenderClear(graphics.renderer);
            if (!end)
            {
                menu(mn, graphics, cursor, e, countmenu, quit, playSound, ingame, options, level, menuSelect, menuChoose, sfxEnabled, massahMusic);
            }
            cursor.draw(graphics); // Chuot de cuoi
            if (ingame)
            {
                SDL_RenderClear(graphics.renderer);
            }
            graphics.presentScene();
        }
        else
        {
            if (onelevel)
            {
                if (level == 0 || player.health <= 0 || playerWinning) // Only reset health when starting a new level
                {
                    player.health = 5;
                }
                player.width = 64;
                player.height = 64;
                player.rect = {static_cast<int>(player.x), static_cast<int>(player.y), player.width, player.height};
                player.character = graphics.loadTexture("sdl_image/chibi/idle/idle.png");
            }
            if (!playerDying && !playerWinning)
            {
                const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
                // Calculate delta time
                Uint32 currentTime = SDL_GetTicks();
                float deltaTime = (currentTime - lastTime) / 1000.0f;
                lastTime = currentTime;
                player.movePlayer(player, currentKeyStates, deltaTime, level);
            }
            else
            {
                if (playerDying && SDL_GetTicks() - stateChangeTime > 500)
                {
                    death(graphics, player, mn, onelevel);
                    playerDying = false;
                    if (player.health <= 0)
                    {
                        gameover(graphics, mn, player, ingame);
                        onemenu = true;
                    }
                }
                if (playerWinning && SDL_GetTicks() - stateChangeTime > 500)
                {
                    win(graphics, player);
                    complete(graphics, mn, player, ingame);
                    playerWinning = false;
                    player.health = 5;
                    level = 0;
                    onelevel = true;
                }
            }

            SDL_RenderClear(graphics.renderer);
            if (level == 1)
            {

                level1(onelevel, graphics, player, mn, level, playerDying, playerWinning, stateChangeTime);
            }
            else if (level == 2)
            {

                level2(onelevel, graphics, player, mn, level, playerDying, playerWinning, stateChangeTime);
            }
            else if (level == 3)
            {
                level3(onelevel, graphics, player, mn, level,
                       playerDying, playerWinning, stateChangeTime);
            }
            drawhealth(graphics, player, mn);
            graphics.presentScene();

            SDL_Delay(16); // ~60 FPS
        }
    }

    Mix_FreeMusic(massahMusic);
    massahMusic = nullptr;
    Mix_CloseAudio();

    return 0;
}
