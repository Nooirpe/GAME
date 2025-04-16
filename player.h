
#ifndef _PLAYER__H
#define _PLAYER__H
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL.h"
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL_image.h"
#include "graphics.h"
#include "animation.h"
#include <iostream>

struct Player
{
    SDL_Texture *character = nullptr;
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *startTexture = nullptr;
    SDL_Texture *animationTexture = nullptr;
    SDL_Texture *jumpTexture = nullptr;
    SDL_Rect rect;
    Animation animation;
    bool isMoving = false;
    bool wasMoving = false; // Lưu trạng thái di chuyển trước đó
    float movetime = 0.0f;  // Thời gian đã di chuyển
    bool isGrounded = false;
    float gravity = 1350.0f;  // Gia tốc trọng trường
    float jumpForce = 400.0f; // Lực nhảy
    float landTimer = 0.0f;
    static constexpr float PLATFORM_HEIGHT = 539.0f; // Change this value to whatever you want

    // Biến cho animation ban đầu
    int startFrame = 0;
    float startFrameTime = 0.0f;
    float startFrameDelay = 0.1f; // Mỗi frame tồn tại 0.1 giây

    // Debug
    bool enableDebug = true;
    bool justSpawned = true;
    bool hasFallen = false;
    bool justLanded = false;

    float x = 400;
    float y = 300;
    float velocityX;
    float velocityY;
    float speed = 200.0f;
    int width;
    int height;
    int health;
    void createPlayer(const Graphics &graphics)
    {
        character = IMG_LoadTexture(graphics.renderer, "C:/C++/GAME/GAME/sdl_image/New folder/player 1.png");
        rect.h = height;
        rect.w = width;
    }
    void spawnPlayer(Graphics &graphics, int spawnX, int spawnY)
    {
        this->x = spawnX;
        this->y = spawnY;
        rect.x = spawnX;
        rect.y = spawnY;
        rect.w = width;
        rect.h = height;
        justSpawned = true;
        hasFallen = false;
    }

    void jump()
    {
        if (isGrounded)
        {
            velocityY = -jumpForce;
            isGrounded = false;
            justLanded = false; // not landed yet
            // Reset movetime and startFrameTime when jumping
            movetime = 0.0f;
            startFrame = 0;
            startFrameTime = 0.0f;
        }
    }

    Player(SDL_Renderer *renderer) : animation(64, 64, 2, 1)
    {
        health = 5;
        idleTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/chibi/idle/idle.png");
        if (idleTexture == nullptr)
        {
            std::cerr << "Failed to load idle texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        animationTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/chibi/run/run.png");
        if (animationTexture == nullptr)
        {
            std::cerr << "Failed to load start texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        startTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/chibi/jump/jump.png");
        if (startTexture == nullptr)
        {
            std::cerr << "Failed to load animation texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }
        jumpTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/chibi/jump/jump 1.png");
        if (jumpTexture == nullptr)
        {
            std::cerr << "Failed to load jump texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }
        animation.setAnimationSpeed(8.0f);
        // Debug: In kích thước các textures
        int w, h;
        if (startTexture)
        {
            SDL_QueryTexture(startTexture, NULL, NULL, &w, &h);
            /*  std::cout << "Start texture dimensions: " << w << "x" << h << std::endl; */
        }
        if (animationTexture)
        {
            SDL_QueryTexture(animationTexture, NULL, NULL, &w, &h);
            /*         std::cout << "Animation texture dimensions: " << w << "x" << h << std::endl; */
        }

        animation.setAnimationSpeed(8.0f);
    }

    ~Player()
    {
        if (idleTexture != nullptr)
            SDL_DestroyTexture(idleTexture);
        if (startTexture != nullptr)
            SDL_DestroyTexture(startTexture);
        if (animationTexture != nullptr)
            SDL_DestroyTexture(animationTexture);
        if (jumpTexture != nullptr)
            SDL_DestroyTexture(jumpTexture);
    }

    void update(float deltaTime)
    {
        // Lưu trạng thái di chuyển hiện tại
        wasMoving = isMoving;
        isMoving = (velocityX != 0 || velocityY != 0);

        // Cập nhật vị trí dựa trên vận tốc
        x += velocityX * deltaTime;
        // Giữ nhân vật trong màn hình
        if (x < 0)
            x = 0;
        if (x > 1366 - width)
            x = 1366 - width;
        if (y < 0)
            y = 0;

        // Cập nhật hướng di chuyển cho animation
        if (velocityX > 0)
        {
            animation.setDirection(Animation::RIGHT);
        }
        else if (velocityX < 0)
        {
            animation.setDirection(Animation::LEFT);
        }
        else if (velocityY > 0)
        {
            animation.setDirection(Animation::DOWN);
        }
        else if (velocityY < 0)
        {
            animation.setDirection(Animation::UP);
        }
        else
        {
            animation.setDirection(Animation::IDLE);
        }

        // Xử lý thời gian di chuyển và animation
        if (isMoving)
        {
            // Nếu trước đó không di chuyển và bây giờ di chuyển
            if (!wasMoving)
            {
                movetime = 0.0f;
                startFrame = 0;
                startFrameTime = 0.0f;
                /*    if (enableDebug)
                   {
                       std::cout << "Started moving - reset timers" << std::endl;
                   } */
            }

            // Luôn tăng movetime khi đang di chuyển
            movetime += deltaTime;

            /*  if (enableDebug && (int)(movetime * 10) % 10 == 0)
             {
                 std::cout << "Moving: " << movetime << "s" << std::endl;
             } */

            // Xử lý animation ban đầu (trong 1 giây đầu)
            if (movetime <= 1.0f)
            {
                startFrameTime += deltaTime;
                if (startFrameTime >= startFrameDelay)
                {
                    startFrameTime = 0.0f;
                    startFrame = (startFrame + 1) % 2;
                    /*  if (enableDebug)
                     {
                         std::cout << "Start animation - Frame: " << startFrame << std::endl;
                     } */
                }
            }
            // Xử lý animation chính (sau 1 giây)
            else
            {
                animation.update(deltaTime);
                /* if (enableDebug && (int)(movetime * 10) % 30 == 0)
                {
                    std::cout << "Main animation - Frame: " << animation.getCurrentFrameIndex() << std::endl;
                } */
            }
        }
        else
        {
            // Reset các giá trị khi dừng
            movetime = 0.0f;
            startFrame = 0;
            startFrameTime = 0.0f;
        }
    }

    void render(SDL_Renderer *renderer)
    {
        SDL_Rect dstRect = {
            static_cast<int>(x),
            static_cast<int>(y),
            width,
            height};

        SDL_RendererFlip flip;
        if (animation.currentDirection == Animation::LEFT)
            flip = SDL_FLIP_NONE;
        else
            flip = SDL_FLIP_HORIZONTAL;

        // CASE 1: Not moving - show idle texture
        if (justLanded)
        {
            if (jumpTexture)
            {
                SDL_RenderCopyEx(renderer, jumpTexture, nullptr, &dstRect, 0, NULL, flip);
            }
            landTimer -= 0.016f;
            if (landTimer <= 0)
            {
                justLanded = false;
                landTimer = 0;
            }
        }
        // CASE 2: Moving for less than 1 second - show start animation
        else if (!isMoving && isGrounded)
        {
            if (idleTexture)
            {
                int texW, texH;
                SDL_QueryTexture(idleTexture, NULL, NULL, &texW, &texH);
                int frameWidth = texW / 8; // 8 frames in idle animation

                int idleFrame = (SDL_GetTicks() / 100) % 8;
                SDL_Rect srcRect = {
                    idleFrame * frameWidth, // Use correct frame width
                    0,
                    frameWidth, // Width from texture size
                    texH        // Full texture height
                };

                SDL_RenderCopyEx(renderer, idleTexture, &srcRect, &dstRect, 0, NULL, flip);
            }
        }
        // CASE 3: in the air - show jump animation
        else if (!isGrounded)
        {
            if (startTexture)
            {
                // Flip based on direction

                SDL_RenderCopyEx(renderer, startTexture, NULL, &dstRect, 0, NULL, flip);
            }
        }

        // CASE 4: Running - show run animation
        else if (isMoving && isGrounded)
        {
            if (animationTexture)
            {
                int texW, texH;
                SDL_QueryTexture(animationTexture, NULL, NULL, &texW, &texH);
                int frameWidth = texW / 7; // 7 frames in run animation

                int runFrame = (SDL_GetTicks() / 100) % 7;
                SDL_Rect srcRect = {
                    runFrame * frameWidth, // Use correct frame width
                    0,
                    frameWidth, // Width from texture size
                    texH        // Full texture height
                };

                SDL_RenderCopyEx(renderer, animationTexture, &srcRect, &dstRect, 0, NULL, flip);
            }
        }
    }

    void movePlayer(Player &player, const Uint8 *currentKeyStates, float deltaTime, int level)
    {
        // Store previous moving state
        player.wasMoving = player.isMoving;

        // Reset horizontal velocity
        player.velocityX = 0;

        // Handle horizontal movement only
        if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
        {
            player.velocityX = -player.speed;
            player.animation.currentDirection = player.animation.LEFT;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
        {
            player.velocityX = player.speed;
            player.animation.currentDirection = player.animation.RIGHT;
        }

        // Handle jump input - only when player is on the ground
        if ((currentKeyStates[SDL_SCANCODE_SPACE] || currentKeyStates[SDL_SCANCODE_UP] ||
             currentKeyStates[SDL_SCANCODE_W]) &&
            player.isGrounded)
        {
            player.jump();
            player.animation.currentDirection = player.animation.UP;
        }
        if (level == 1)
        {
            bool isOverGap = ((player.x + player.width) > 430 && player.x < 435) ||
                             ((player.x + player.width) > 915 && player.x < 920);
            // IMMEDIATELY make the player not grounded when over a gap
            if (isOverGap)
            {
                player.isGrounded = false;

                // Set hasFallen only when they actually drop below platform level
                if (player.y >= PLATFORM_HEIGHT - 10)
                {
                    player.hasFallen = true;
                    player.justSpawned = false;
                }
            }
            // ALWAYS apply gravity when not grounded
            if (!player.isGrounded)
            {
                // Increase falling speed (gravity effect)
                player.velocityY += player.gravity * deltaTime;

                // Update position based on velocity
                player.y += player.velocityY * deltaTime;

                // Check if player landed on platform
                if (player.y >= PLATFORM_HEIGHT + 13 - player.height && !isOverGap && !player.hasFallen)
                {
                    player.y = PLATFORM_HEIGHT + 13 - player.height;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    // landing animation
                    player.justLanded = true;
                    player.landTimer = 0.2f; // Reset timer for landing animation
                    if (player.velocityX == 0)
                        player.animation.currentDirection = player.animation.IDLE;
                }
                // Neu roi qua y = 700 thi chet
                if (player.y > 730 && isOverGap)
                {
                    player.y = 730;
                }
            }

            // Update horizontal position
            player.x += player.velocityX * deltaTime;

            // Apply horizontal boundaries
            if (player.x < 0)
                player.x = 0;
            if (player.x > 1300 - player.width)
                player.x = 1300 - player.width;

            // Check if player is over the gap
            if (isOverGap)
            {
                // Player is not grounded when over a gap
                player.isGrounded = false;
                if (player.y >= PLATFORM_HEIGHT - 10)
                {
                    player.justSpawned = false;
                    player.hasFallen = true;
                }
            }
        }
        if (level == 2)
        {

            if (!player.isGrounded)
            {
                // Apply gravity
                player.velocityY += player.gravity * deltaTime;

                // Update vertical position
                player.y += player.velocityY * deltaTime;
                bool onPlatform = false;
                if (player.x + player.width > 350 && player.x < 406 &&
                    player.y + player.height <= PLATFORM_HEIGHT - 33 + 5 &&  // Add small tolerance
                    player.y + player.height >= PLATFORM_HEIGHT - 33 - 10 && // Check if close enough
                    player.velocityY > 0)                                    // Only land when falling down
                {
                    player.y = PLATFORM_HEIGHT - player.height - 33;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    player.justLanded = true;
                    player.landTimer = 0.2f;
                    onPlatform = true;
                }

                // Platform 2: x from 410 to 460, height = 71
                else if (player.x + player.width > 430 && player.x < 460 &&
                         player.y + player.height <= PLATFORM_HEIGHT - 71 + 5 &&
                         player.y + player.height >= PLATFORM_HEIGHT - 71 - 10 &&
                         player.velocityY > 0)
                {
                    player.y = PLATFORM_HEIGHT - player.height - 71;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    player.justLanded = true;
                    player.landTimer = 0.2f;
                    onPlatform = true;
                }

                // Platform 3: x from 465 to 736, height = 111
                else if (player.x + player.width > 480 && player.x < 736 &&
                         player.y + player.height <= PLATFORM_HEIGHT - 111 + 5 &&
                         player.y + player.height >= PLATFORM_HEIGHT - 111 - 10 &&
                         player.velocityY > 0)
                {
                    player.y = PLATFORM_HEIGHT - player.height - 111;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    player.justLanded = true;
                    player.landTimer = 0.2f;
                    onPlatform = true;
                }

                // Platform 4: x from 811 to 860, height = 52
                else if (player.x + player.width > 811 && player.x < 860 &&
                         player.y + player.height <= PLATFORM_HEIGHT - 52 + 5 &&
                         player.y + player.height >= PLATFORM_HEIGHT - 52 - 10 &&
                         player.velocityY > 0)
                {
                    player.y = PLATFORM_HEIGHT - player.height - 52;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    player.justLanded = true;
                    player.landTimer = 0.2f;
                    onPlatform = true;
                }

                // Platform 5: x from 928 to 1015, height = 16
                else if (player.x + player.width > 948 && player.x < 995 &&
                         player.y + player.height <= PLATFORM_HEIGHT - 16 + 5 &&
                         player.y + player.height >= PLATFORM_HEIGHT - 16 - 10 &&
                         player.velocityY > 0)
                {
                    player.y = PLATFORM_HEIGHT - player.height - 16;
                    player.velocityY = 0;
                    player.isGrounded = true;
                    player.justLanded = true;
                    player.landTimer = 0.2f;
                    onPlatform = true;
                }
                // Check if player should land on the flat platform
                else if (player.y >= PLATFORM_HEIGHT + 13 - player.height && player.velocityY > 0)
                {
                    // Land on platform
                    player.y = PLATFORM_HEIGHT + 13 - player.height;
                    player.velocityY = 0;
                    player.isGrounded = true;

                    // Show landing animation
                    player.justLanded = true;
                    player.landTimer = 0.2f;

                    if (player.velocityX == 0)
                        player.animation.currentDirection = player.animation.IDLE;
                }
            }
            if (player.isGrounded) // Player is grounded
            {
                // Check if player is still on a platform
                bool stillOnPlatform = false;

                // Platform 1
                if (player.x + player.width > 350 && player.x < 406 &&
                    player.y + player.height == PLATFORM_HEIGHT - 33)
                {
                    stillOnPlatform = true;
                }
                // Platform 2
                else if (player.x + player.width > 430 && player.x < 460 &&
                         player.y + player.height == PLATFORM_HEIGHT - 71)
                {
                    stillOnPlatform = true;
                }
                // Platform 3
                else if (player.x + player.width > 480 && player.x < 736 &&
                         player.y + player.height == PLATFORM_HEIGHT - 111)
                {
                    stillOnPlatform = true;
                }
                // Platform 4
                else if (player.x + player.width > 811 && player.x < 860 &&
                         player.y + player.height == PLATFORM_HEIGHT - 52)
                {
                    stillOnPlatform = true;
                }
                // Platform 5
                else if (player.x + player.width > 948 && player.x < 995 &&
                         player.y + player.height == PLATFORM_HEIGHT - 16)
                {
                    stillOnPlatform = true;
                }
                // Main floor
                else if (player.y + player.height == PLATFORM_HEIGHT + 13)
                {
                    stillOnPlatform = true;
                }

                // FALL
                if (!stillOnPlatform)
                {
                    player.isGrounded = false;
                }
            }

            // Update horizontal position
            player.x += player.velocityX * deltaTime;

            // Apply horizontal boundaries
            if (player.x < 0)
                player.x = 0;
            if (player.x > 1300 - player.width)
                player.x = 1300 - player.width;
            if (player.y + player.height > PLATFORM_HEIGHT - 33 &&
                player.y < PLATFORM_HEIGHT - 33 + 33)
            {
                // Left boundary - block exactly at x=350
                if (player.x + player.width > 370 && player.x < 370)
                {
                    player.x = 370 - player.width;
                }
            }

            // Platform 2 boundaries collision (430-460, height 71)
            if (player.y + player.height > PLATFORM_HEIGHT - 71 &&
                player.y < PLATFORM_HEIGHT - 71 + 71)
            {
                // Left boundary - block exactly at x=430
                if (player.x + player.width > 430 && player.x < 430)
                {
                    player.x = 430 - player.width;
                }
                // Right boundary - block exactly at x=460
                if (player.x < 460 && player.x + player.width > 460)
                {
                    player.x = 460;
                }
            }

            // Platform 3 boundaries collision (480-736, height 111)
            if (player.y + player.height > PLATFORM_HEIGHT - 111 &&
                player.y < PLATFORM_HEIGHT - 111 + 111)
            {
                // Left boundary - block exactly at x=480
                if (player.x + player.width > 490 && player.x < 490)
                {
                    player.x = 490 - player.width;
                }
                // Right boundary - block exactly at x=736
                if (player.x < 736 && player.x + player.width > 736)
                {
                    player.x = 736;
                }
            }

            // Platform 4 boundaries collision (811-860, height 52)
            if (player.y + player.height > PLATFORM_HEIGHT - 52 &&
                player.y < PLATFORM_HEIGHT - 52 + 52)
            {
                // Left boundary - block exactly at x=811
                if (player.x + player.width > 811 && player.x + player.width < 811)
                {
                    player.x = 811 - player.width;
                }
                // Right boundary - block exactly at x=860
                if (player.x < 840 && player.x + player.width > 840)
                {
                    player.x = 840;
                }
            }

            // Platform 5 boundaries collision (928-1015, height 16)
            if (player.y + player.height > PLATFORM_HEIGHT - 16 &&
                player.y < PLATFORM_HEIGHT - 16 + 16)
            {
                // Left boundary - block exactly at x=928
                if (player.x + player.width > 948 && player.x < 948)
                {
                    player.x = 948 - player.width;
                }
                // Right boundary - block exactly at x=1015
                if (player.x < 995 && player.x + player.width > 995)
                {
                    player.x = 995;
                }
            }
        }

        // Set moving state based on any movement (horizontal or vertical)
        player.isMoving = (player.velocityX != 0 || !player.isGrounded);

        if (player.isMoving && !player.wasMoving)
        {
            // Started moving
            player.movetime = 0.0f;
            player.startFrame = 0;
            player.startFrameTime = 0.0f;
        }
        else if (player.isMoving)
        {
            // Continue moving
            player.movetime += deltaTime;
        }
        // Update collision rect
        player.rect.x = static_cast<int>(player.x);
        player.rect.y = static_cast<int>(player.y);

        // Update animation
        player.animation.update(deltaTime);
    }
};
#endif