#ifndef _PLAYER__H
#define _PLAYER__H
#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Core/graphics.h"
#include "../Systems/animation.h"
#include <iostream>
#include <vector>

// Forward declaration
struct Platform;

/**
 * @struct Player
 * @brief Represents the player character in the game
 */
struct Player
{
    // Constants
    static constexpr float PLATFORM_HEIGHT = 539.0f;

    // Constructor and Destructor
    Player(SDL_Renderer *renderer);
    ~Player();

    // Core functions
    void spawnPlayer(int spawnX, int spawnY);
    void update(float deltaTime);
    void render(SDL_Renderer *renderer, float deltaTime);
    void handleInput(const Uint8 *currentKeyStates, float deltaTime, int level);

    // Action functions
    void jump();
    void attack();
    void takeDamage(int damageDirection = 0); // Added direction parameter for knockback

    // Physics functions
    void applyGravity(float deltaTime);
    void checkPlatformCollisions(int level);
    void applyHorizontalMovement(float deltaTime);
    void checkBoundaries(int level);

    // Basic elements
    float x = 400;
    float y = 300;
    float velocityX = 0;
    float velocityY = 0;
    float speed = 200.0f;
    int width = 64;
    int height = 64;
    int health = 5;
    SDL_Rect rect;

    // Movement states
    bool isMoving = false;
    bool wasMoving = false;
    float movetime = 0.0f;
    bool isGrounded = false;
    float gravity = 1350.0f;
    float jumpForce = 500.0f;
    bool justSpawned = true;
    bool hasFallen = false;

    // Animation
    Animation animation;
    float landTimer = 0.0f;
    bool justLanded = false;

    SDL_Texture *character = nullptr;
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *startTexture = nullptr;
    SDL_Texture *animationTexture = nullptr;
    SDL_Texture *jumpTexture = nullptr;
    SDL_Texture *attackTexture = nullptr;

    // Animation frame counts
    static const int IDLE_FRAMES = 8;
    static const int RUN_FRAMES = 7;
    static const int ATTACK_FRAMES = 8;

    // Start animation
    int startFrame = 0;
    float startFrameTime = 0.0f;

    // Attack states
    bool isAttacking = false;
    float attackTimer = 0.0f;
    float attackDuration = 0.8f; // Tăng từ 0.5f lên 0.8f để animation hoàn thành đầy đủ
    int attackFrame = 0;
    int attackDamage = 1;
    SDL_Rect attackHitbox;
    Animation::Direction lastDirection = Animation::RIGHT;

    // Damage states
    bool isImmune = false;
    float immuneTimer = 0.0f;
    float immuneDuration = 1.0f;
    bool showPlayer = true;
    float blinkTimer = 0.0f;

    // Knockback states
    bool isKnockback = false;
    float knockbackTimer = 0.0f;
    float knockbackDuration = 0.3f;
    float knockbackForceX = 300.0f;
    float knockbackForceY = 200.0f;
    int knockbackDirection = 0;

    // Debugging
    bool enableDebug = true;

private:
    // Handle player movement and animation
    void updateAttackState(float deltaTime);
    void updateImmunityState(float deltaTime);
    void updateMovementAnimation();
    void updateKnockbackState(float deltaTime);
    void handleLevelOneCollisions();
    void handleLevelTwoCollisions();
    void handleLevelThreeCollisions();
    bool checkPlatformLanding(float left, float right, float platformHeight, float tolerance);
    bool isOnPlatform(float left, float right, float platformHeight);
};
#endif