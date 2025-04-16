#ifndef _STAGE__H
#define _STAGE__H

#include <C:\C++\GAME\GAME\src\include\SDL2\SDL.h>
#include "game.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "player.h"
using namespace std;

/* void level1(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *mn, int &level)
{
    static SDL_Texture *mapTexture = nullptr;
    if (onelevel)
    {
        mapTexture = graphics.loadTexture("sdl_image\\Things\\Map\\map 1.png");
        player.spawnPlayer(graphics, 54, Player::PLATFORM_HEIGHT + 25 - player.height);
        SDL_RenderClear(graphics.renderer);
        if (mn)
            graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 0;
    }
    SDL_RenderClear(graphics.renderer);
    // Draw map (using our persistent texture)
    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }
    player.render(graphics.renderer);
    graphics.presentScene();
    if (player.rect.x > 1156 && player.rect.x + player.rect.w < 1275 && player.rect.y > (Player::PLATFORM_HEIGHT + 3) && player.rect.y + player.rect.h < 768)
    {
        win(graphics, player);
        level++;
        player.x = 70;
        player.y = 155;
        onelevel = 1;
    }

    /* else if (player.rect.x > 0 && player.rect.x + player.rect.w < 1147 && player.rect.y > 0 && player.rect.y + player.rect.h < 767)
    {
        mn = graphics.loadTexture("sdl_image\\Things\\Map\\map 1.png");
    }
    else
    {
        player.health--;
        death(graphics, player, mn, onelevel);
    } */
/*    graphics.prepareImg(mn);
   SDL_DestroyTexture(mn); */
void level1(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime)
{
    static SDL_Texture *mapTexture = nullptr;
    if (onelevel)
    {
        mapTexture = graphics.loadTexture("sdl_image\\Things\\Map\\map 1.png");
        // Reset player position
        player.x = 54;
        player.y = Player::PLATFORM_HEIGHT + 13 - player.height;
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;
        onelevel = false;
    }

    // Draw the map
    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }

    // Render player
    player.render(graphics.renderer);

    // Check win condition
    if (player.x > 1156 && player.y > 425)
    {
        if (!playerWinning)
        {
            playerWinning = true;
            stateChangeTime = SDL_GetTicks();
        }
    }

    // Check death condition
    else if (player.y > 700 && !playerDying)
    {
        playerDying = true;
        stateChangeTime = SDL_GetTicks();
    }
}

#endif