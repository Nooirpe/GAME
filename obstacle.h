#ifndef _OBSTACLE__H
#define _OBSTACLE__H
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL.h"
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL_image.h"
#include "graphics.h"
#include <bits/stdc++.h>
#include "player.h"
#include "animation.h"
using namespace std;
struct Bat
{
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *flyTexture = nullptr;
    SDL_Texture *attackTexture = nullptr;
    SDL_Texture *dieTexture = nullptr;

    // Vi tri va chuyen dong
    float x = 0.0f;
    float y = 0.0f;
    float speed = 100.0f;

    // Khong gian
    int width = 64;
    int height = 64;

    // Boundaries
    float leftBoundary = 500.0f;
    float rightBoundary = 600.0f;

    // Huong (1 = phai, -1 = trai)
    int direction = 1;

    // Animation
    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.1f; // Thoi gian cho moi frame

    // Number of frames
    int idleFrames = 12;
    int flyFrames = 8;
    int attackFrames = 8;
    int dieFrames = 8;

    // State
    enum State
    {
        IDLE,
        FLY,
        ATTACK,
        DIE
    };
    State currentState = FLY;
    bool isDead = false;
    SDL_Rect rect;

    // Animation object
    void spawnBat(float spawnX, float spawnY, float leftBound, float rightBound)
    {
        // Set position
        x = spawnX;
        y = spawnY;

        // Set movement boundaries
        leftBoundary = leftBound;
        rightBoundary = rightBound;

        // Reset movement and animation state
        direction = 1; // Start moving right
        currentFrame = 0;
        frameTime = 0.0f;
        currentState = FLY;

        // Reset collision rectangle
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = width;
        rect.h = height;

        // Reset death state
        isDead = false;
    }

    void createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound)
    {
        x = startX;
        y = startY;
        leftBoundary = leftBound;
        rightBoundary = rightBound;

        idleTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Idle/Idle.png");
        flyTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Fly/Fly.png");
        attackTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Attack/Attack.png");
        dieTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Die/Die.png");

        // Query
        int textureWidth, textureHeight;
        if (flyTexture)
        {
            SDL_QueryTexture(flyTexture, NULL, NULL, &textureWidth, &textureHeight);

            int frameWidth = textureWidth / flyFrames;
            int frameHeight = textureHeight;
            float scale = 0.5f;
            width = static_cast<int>(frameWidth * scale);
            height = static_cast<int>(frameHeight * scale);
        }

        rect = {static_cast<int>(x), static_cast<int>(y), width, height};
    }
    // Update bat position
    void update(float deltaTime, const Player &player)
    {
        if (currentState == DIE)
        {
            updateAnimation(deltaTime);
            return;
        }

        // Kiem tra neu bat gan player
        float horizontalDistance = abs((x + width / 2) - (player.x + player.width / 2));
        float verticalDistance = abs((y + height / 2) - (player.y + player.height / 2));

        bool playerInRange = (horizontalDistance < 100 && verticalDistance < height);

        if (playerInRange && currentState != ATTACK && currentState != DIE)
        {
            // Neu o gan, attack
            currentState = ATTACK;
            currentFrame = 0;
            frameTime = 0.0f;
        }
        else if (currentState == ATTACK)
        {
            if (currentFrame >= attackFrames - 1 && frameTime >= frameDuration)
            {
                currentState = FLY;
                currentFrame = 0;
                frameTime = 0.0f;
            }
        }
        else
        {
            // Bay binh thuong
            currentState = FLY;
            x += direction * speed * deltaTime;
            if (x <= leftBoundary)
            {
                // cham lai khi tien den boundary
                float distanceToBoundary = x - leftBoundary;
                if (distanceToBoundary < -5)
                    x = leftBoundary;
                direction = 1;
            }
            else if (x + width >= rightBoundary)
            {
                float distanceToBoundary = (x + width) - rightBoundary;
                if (distanceToBoundary > 5)
                    x = rightBoundary - width;
                direction = -1;
            }
        }
        // Update collision rect
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);

        updateAnimation(deltaTime);
    }

    // Update animation frame
    void updateAnimation(float deltaTime)
    {
        frameTime += deltaTime;
        if (frameTime >= frameDuration)
        {
            frameTime = 0.0f;
            switch (currentState)
            {
            case IDLE:
                currentFrame = (currentFrame + 1) % idleFrames;
                break;
            case FLY:
                currentFrame = (currentFrame + 1) % flyFrames;
                break;
            case ATTACK:
                if (currentFrame < attackFrames - 1)
                    currentFrame++;
                break;
            case DIE:
                if (currentFrame < dieFrames - 1)
                    currentFrame++;
                else
                    isDead = true;
                break;
            }
        }
    }
    // Bat chet
    void die()
    {
        if (currentState != DIE && !isDead)
        {
            currentState = DIE;
            currentFrame = 0;
            frameTime = 0;
        }
    }
    void render(SDL_Renderer *renderer)
    {

        if (isDead)
            return;
        SDL_Texture *currentTexture = nullptr;
        int frameCount = 0;
        switch (currentState)
        {
        case IDLE:
            currentTexture = idleTexture;
            frameCount = idleFrames;
            break;
        case FLY:
            currentTexture = flyTexture;
            frameCount = flyFrames;
            break;
        case ATTACK:
            currentTexture = attackTexture;
            frameCount = attackFrames;
            break;
        case DIE:
            currentTexture = dieTexture;
            frameCount = dieFrames;
            break;
        }
        if (currentTexture)
        {
            int textureWidth, textureHeight;
            SDL_QueryTexture(currentTexture, NULL, NULL, &textureWidth, &textureHeight);

            int sourceFrameWidth = textureWidth / frameCount;
            int sourceFrameHeight = textureHeight;
            // Calculate source rectangle
            SDL_Rect srcRect = {
                currentFrame * sourceFrameWidth, // x position in spritesheet
                0,                               // y position in spritesheet
                sourceFrameWidth,                // width of each frame
                sourceFrameHeight                // height of each frame
            };
            // Vi tri rectangle
            SDL_Rect destRect = {
                static_cast<int>(x),
                static_cast<int>(y),
                width, height};
            SDL_RendererFlip flip = (direction < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            // render the bat
            SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &destRect, 0, NULL, flip);
        }
    }
    // Check if bat collides with player
    bool collidesWithPlayer(const Player &player, SDL_Renderer *renderer = nullptr)
    {
        if (isDead)
            return false;
        // Calculate offset as a percentage of width/height for better scaling
        int batOffsetX = width * 0.2;  // 15% of width
        int batOffsetY = height * 0.3; // 15% of height
        int playerOffsetX = player.width * 0.2;
        int playerOffsetY = player.height * 0.2;

        SDL_Rect batCollision = {
            static_cast<int>(x + batOffsetX),
            static_cast<int>(y + batOffsetY),
            width - batOffsetX * 2,
            height - batOffsetY * 2};

        SDL_Rect playerCollision = {
            static_cast<int>(player.x + playerOffsetX),
            static_cast<int>(player.y + playerOffsetY),
            player.width - playerOffsetX * 2,
            player.height - playerOffsetY * 2};
        if (currentState == ATTACK)
        {
            bool atSameY = abs((y + height / 2) - (player.y + player.height / 2)) < height * 0.7;
            if (atSameY)
            {
                if (direction > 0)
                {
                    batCollision.w += width * 0.2;
                }
                else
                {
                    batCollision.x -= width * 0.2;
                    batCollision.w += width * 0.2;
                }
            }
        }
        if (renderer != nullptr)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for bat
            SDL_RenderDrawRect(renderer, &batCollision);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for player
            SDL_RenderDrawRect(renderer, &playerCollision);
        }

        return SDL_HasIntersection(&batCollision, &playerCollision);
    }
};
#endif