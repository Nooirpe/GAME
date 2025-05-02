#ifndef _OBSTACLE__H
#define _OBSTACLE__H
#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Core/graphics.h"
#include <bits/stdc++.h>
#include "player.h"
#include "../Systems/animation.h"
using namespace std;

/**
 * @struct Bat
 * @brief Quái vật bay trong game, di chuyển qua lại và tấn công người chơi
 */
struct Bat
{
    // Textures
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *flyTexture = nullptr;
    SDL_Texture *dieTexture = nullptr;
    SDL_Texture *hurtTexture = nullptr;

    // Vị trí và kích thước
    float x = 0.0f;
    float y = 0.0f;
    float speed = 100.0f;
    int width = 64;
    int height = 64;

    // Giới hạn di chuyển
    float leftBoundary = 500.0f;
    float rightBoundary = 600.0f;
    int direction = 1;

    // Animation properties
    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.1f;

    // Frame counts cho mỗi trạng thái
    int idleFrames = 12;
    int flyFrames = 8;
    int hurtFrames = 8;
    int dieFrames = 8;

    // Trạng thái
    int hitCount = 0;       // Số lần bị đánh
    float hurtTimer = 0.0f; // Timer cho animation hurt
    enum State
    {
        IDLE,
        FLY,
        HURT,
        DIE
    };
    State currentState = FLY;
    bool isDead = false;
    SDL_Rect rect;

    // Main functions
    void spawnBat(float spawnX, float spawnY, float leftBound, float rightBound);
    void createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound);
    void update(float deltaTime, const Player &player);
    void updateAnimation(float deltaTime);
    void hurt(); // Xử lý khi bị thương
    void die();  // Xử lý khi chết
    void render(SDL_Renderer *renderer);
    bool collidesWithPlayer(const Player &player, SDL_Renderer *renderer = nullptr);
    bool checkAttackCollision(const SDL_Rect &attackHitbox, SDL_Renderer *renderer = nullptr);

private:
    // Others
    void LoadTextures(SDL_Renderer *renderer);
    void CalculateDimensions();
    void UpdateMovement(float deltaTime);
    void HandleBoundaryCollisions();
    void RenderCurrentFrame(SDL_Renderer *renderer, SDL_Texture *texture, int frameCount);
    SDL_Rect CalculateBatHitbox();
    SDL_Rect CalculatePlayerHitbox(const Player &player);
    void ApplyDamageToPlayer(const Player &player);
};

#endif