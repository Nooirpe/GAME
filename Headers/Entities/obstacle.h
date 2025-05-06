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
 * @brief Enemy that flies and attacks the player
 */
struct Bat
{
    // Textures
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
    int flyFrames = 8;
    int hurtFrames = 8;
    int dieFrames = 8;

    // Trạng thái
    int hitCount = 0;       // Số lần bị đánh
    float hurtTimer = 0.0f; // Timer cho animation hurt
    enum State
    {
        FLY,
        HURT,
        DIE
    };
    State currentState = FLY;
    bool isDead = false;
    SDL_Rect rect;

    // Phương thức chính
    /**
     * @brief Spawns a bat at the specified position with movement boundaries
     */
    void spawnBat(float spawnX, float spawnY, float leftBound, float rightBound);

    /**
     * @brief Creates a bat with textures and initial parameters
     */
    void createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound);

    /**
     * @brief Updates the bat state each frame
     */
    void update(float deltaTime);

    /**
     * @brief Updates animation based on current state
     */
    void updateAnimation(float deltaTime);

    void hurt();

    void die();

    void render(SDL_Renderer *renderer);

    bool collidesWithPlayer(const Player &player);

    bool checkAttackCollision(const SDL_Rect &attackHitbox, SDL_Renderer *renderer = nullptr);

private:
    /**
     * @brief Loads all required textures
     */
    void LoadTextures(SDL_Renderer *renderer);

    /**
     * @brief Calculates bat dimensions based on texture
     */
    void CalculateDimensions();

    /**
     * @brief Handles bat movement logic
     */
    void UpdateMovement(float deltaTime);

    /**
     * @brief Handles collision with movement boundaries
     */
    void HandleBoundaryCollisions();

    void RenderCurrentFrame(SDL_Renderer *renderer, SDL_Texture *texture, int frameCount);

    SDL_Rect CalculateBatHitbox();

    SDL_Rect CalculatePlayerHitbox(const Player &player);

    void ApplyDamageToPlayer(const Player &player);
};

#endif