#ifndef _STAGE__H
#define _STAGE__H

#include <C:\C++\GAME\GAME\src\include\SDL2\SDL.h>
#include "game.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "obstacle.h"
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
void level2(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime)
{
    static SDL_Texture *mapTexture = nullptr;

    if (onelevel)
    {
        mapTexture = graphics.loadTexture("sdl_image\\Things\\Map\\map 2.png");
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
    int collisionOffset = 12; // Adjust this value to make the collision box smaller
    SDL_Rect playerCollisionBox = {
        static_cast<int>(player.x + collisionOffset),
        static_cast<int>(player.y + collisionOffset),
        player.width - (collisionOffset * 2),
        player.height - (collisionOffset * 2)};

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
    else if (((
                  (playerCollisionBox.x + playerCollisionBox.w > 249) && (playerCollisionBox.x < 269) &&
                  (playerCollisionBox.y + playerCollisionBox.h > 522) && (playerCollisionBox.y < 535)) ||

              ((playerCollisionBox.x + playerCollisionBox.w > 750) && (playerCollisionBox.x < 800) &&
               (playerCollisionBox.y + playerCollisionBox.h > 522) && (playerCollisionBox.y < 535)) ||

              ((playerCollisionBox.x + playerCollisionBox.w > 960) && (playerCollisionBox.x < 974) &&
               (playerCollisionBox.y + playerCollisionBox.h > 494) && (playerCollisionBox.y < 505))) &&
             !playerDying)
    {

        playerDying = true;
        stateChangeTime = SDL_GetTicks();
    }
}
void level3(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime)
{

    static SDL_Texture *mapTexture = nullptr;
    static Bat bat;
    static bool batInitialized = false;
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;
    if (onelevel)
    {
        mapTexture = graphics.loadTexture("sdl_image\\Things\\Map\\map 3.png");
        // Reset player position
        player.x = 54;
        player.y = Player::PLATFORM_HEIGHT + 13 - player.height;
        bat.width = player.width;
        bat.height = player.height;
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;
        if (!batInitialized)
        {
            bat.createBat(graphics, 500, 300, 400, 800);
            batInitialized = true;
        }
        else
            bat.spawnBat(500, 300, 400, 800);
        bat.width = player.width;
        bat.height = player.height;

        // Update rect with new dimensions
        bat.rect.w = bat.width;
        bat.rect.h = bat.height;

        onelevel = false;
    }

    // Draw the map
    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }
    int collisionOffset = 12; // Adjust this value to make the collision box smaller
    SDL_Rect playerCollisionBox = {
        static_cast<int>(player.x + collisionOffset),
        static_cast<int>(player.y + collisionOffset),
        player.width - (collisionOffset * 2),
        player.height - (collisionOffset * 2)};

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
    else if (((
                  (playerCollisionBox.x + playerCollisionBox.w > 300) && (playerCollisionBox.x < 360) &&
                  (playerCollisionBox.y + playerCollisionBox.h > 510) && (playerCollisionBox.y < 535)) ||

              ((playerCollisionBox.x + playerCollisionBox.w > 435) && (playerCollisionBox.x < 480) &&
               (playerCollisionBox.y + playerCollisionBox.h > 430) && (playerCollisionBox.y < 465)) ||

              ((playerCollisionBox.x + playerCollisionBox.w > 780) && (playerCollisionBox.x < 815) &&
               (playerCollisionBox.y + playerCollisionBox.h > 375) && (playerCollisionBox.y < 400))) &&
             !playerDying)
    {
        playerDying = true;
        stateChangeTime = SDL_GetTicks();
    }
    if (batInitialized)
    {
        bat.update(deltaTime, player);
        if (bat.collidesWithPlayer(player, graphics.renderer) && bat.currentState != Bat::DIE)
        {
            player.health--;
            bat.die();
        }
        bat.render(graphics.renderer);
    }
}

#endif