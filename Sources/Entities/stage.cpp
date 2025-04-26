#include "../../Headers/Entities/stage.h"
#include "../../Headers/Entities/player.h"
#include "../../Headers/Core/graphics.h"
#include "../../Headers/Entities/obstacle.h"

void level1(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime)
{
    static SDL_Texture *mapTexture = nullptr;
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    if (onelevel)
    {
        mapTexture = graphics.loadTexture("Assets\\Things\\Map\\map 1.png");
        player.x = 54;
        player.y = Player::PLATFORM_HEIGHT + 13 - player.height;
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;
        onelevel = false;
    }

    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }

    // Update player
    player.update(deltaTime);

    // Render player
    player.render(graphics.renderer, deltaTime);

    if (player.x > 1156 && player.y > 425)
    {
        if (!playerWinning)
        {
            playerWinning = true;
            stateChangeTime = SDL_GetTicks();
        }
    }
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
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    if (onelevel)
    {
        mapTexture = graphics.loadTexture("Assets\\Things\\Map\\map 2.png");
        player.x = 54;
        player.y = Player::PLATFORM_HEIGHT + 13 - player.height;
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;
        onelevel = false;
    }

    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }

    SDL_Rect playerCollisionBox = {
        static_cast<int>(player.x + 12),
        static_cast<int>(player.y + 12),
        player.width - 24,
        player.height - 24};

    // Update player
    player.update(deltaTime);

    // Render player
    player.render(graphics.renderer, deltaTime);

    if (player.x > 1156 && player.y > 425)
    {
        if (!playerWinning)
        {
            playerWinning = true;
            stateChangeTime = SDL_GetTicks();
        }
    }
    else if (((playerCollisionBox.x + playerCollisionBox.w > 249 && playerCollisionBox.x < 269 &&
               playerCollisionBox.y + playerCollisionBox.h > 522 && playerCollisionBox.y < 535) ||
              (playerCollisionBox.x + playerCollisionBox.w > 750 && playerCollisionBox.x < 800 &&
               playerCollisionBox.y + playerCollisionBox.h > 522 && playerCollisionBox.y < 535) ||
              (playerCollisionBox.x + playerCollisionBox.w > 962 && playerCollisionBox.x < 980 &&
               playerCollisionBox.y + playerCollisionBox.h > 498 && playerCollisionBox.y < 509)) &&
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
        mapTexture = graphics.loadTexture("Assets\\Things\\Map\\map 3.png");
        player.x = 54;
        player.y = Player::PLATFORM_HEIGHT + 13 - player.height;
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;
        if (!batInitialized)
        {
            bat.createBat(graphics, 500, 300, 400, 800);
            batInitialized = true;
        }
        onelevel = false;
    }

    if (mapTexture != nullptr)
    {
        SDL_RenderCopy(graphics.renderer, mapTexture, NULL, NULL);
    }

    // Update player
    player.update(deltaTime);

    // Render player
    player.render(graphics.renderer, deltaTime);

    if (player.x > 1156 && player.y > 425)
    {
        if (!playerWinning)
        {
            playerWinning = true;
            stateChangeTime = SDL_GetTicks();
        }
    }
    else if (batInitialized)
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