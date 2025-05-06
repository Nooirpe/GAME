
#include "../../Headers/States/stage.h"
#include "../../Headers/Entities/player.h"
#include "../../Headers/Core/graphics.h"
#include "../../Headers/Entities/obstacle.h"

void level1(bool &onelevel, Graphics &graphics, Player &player,
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
        player.velocityX = 0;
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
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        }
    }
    else if (player.y > 700 && !playerDying)
    {
        // Dừng di chuyển khi nhân vật chết
        player.velocityX = 0;
        player.velocityY = 0;
        playerDying = true;
        stateChangeTime = SDL_GetTicks();
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    }
}

void level2(bool &onelevel, Graphics &graphics, Player &player,
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
        player.velocityX = 0;
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
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
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
        // Dừng di chuyển khi nhân vật chết
        player.velocityX = 0;
        player.velocityY = 0;
        playerDying = true;
        stateChangeTime = SDL_GetTicks();
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    }
}

void level3(bool &onelevel, Graphics &graphics, Player &player,
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
        player.velocityX = 0; // Đặt lại vận tốc ngang khi respawn
        player.velocityY = 0;
        player.isGrounded = true;
        player.hasFallen = false;
        player.justSpawned = true;

        // Reset bat's state completely when entering level
        if (!batInitialized)
        {
            bat.createBat(graphics, 500, 300, 400, 800);
            batInitialized = true;
        }
        else
        {
            // Reset existing bat
            bat.isDead = false;
            bat.hitCount = 0;
            bat.currentState = Bat::FLY;
            bat.currentFrame = 0;
            bat.frameTime = 0.0f;
            bat.x = 500;
            bat.y = 300;
            bat.direction = 1;
        }

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

    // Kiểm tra chiến thắng
    if (player.x > 1156 && player.y > 425)
    {
        if (!playerWinning)
        {
            playerWinning = true;
            stateChangeTime = SDL_GetTicks();
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        }
    }

    // Xử lý logic liên quan đến bat
    if (batInitialized && !playerDying && !playerWinning)
    {
        bat.update(deltaTime);

        if (player.isAttacking && bat.checkAttackCollision(player.attackHitbox, graphics.renderer) &&
            bat.currentState != Bat::DIE && bat.currentState != Bat::HURT)
        {
            bat.hurt(); // Bat bị thương khi bị đánh trúng
        }

        // Kiểm tra va chạm của nhân vật với bat để trừ máu player
        if (bat.collidesWithPlayer(player) &&
            bat.currentState != Bat::DIE && bat.currentState != Bat::HURT)
        {
            if (player.health > 0)
                player.takeDamage();
            else
            {
                player.velocityX = 0;
                player.velocityY = 0;
                playerDying = true;
                stateChangeTime = SDL_GetTicks();
                SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
            }
        }

        bat.render(graphics.renderer);
    }

    // Kiểm tra va chạm với các khu vực nguy hiểm
    if (((playerCollisionBox.x + playerCollisionBox.w > 310 && playerCollisionBox.x < 335 &&
          playerCollisionBox.y + playerCollisionBox.h > 505 && playerCollisionBox.y < 535) ||
         (playerCollisionBox.x + playerCollisionBox.w > 442 && playerCollisionBox.x < 482 &&
          playerCollisionBox.y + playerCollisionBox.h > 439 && playerCollisionBox.y < 469) ||
         (playerCollisionBox.x + playerCollisionBox.w > 773 && playerCollisionBox.x < 790 &&
          playerCollisionBox.y + playerCollisionBox.h > 379 && playerCollisionBox.y < 400)) &&
        !playerDying && !playerWinning)
    {
        // Dừng di chuyển khi nhân vật chết
        player.velocityX = 0;
        player.velocityY = 0;
        playerDying = true;
        stateChangeTime = SDL_GetTicks();
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    }
}
