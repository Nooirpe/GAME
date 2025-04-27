#ifndef _PLAYER__H
#define _PLAYER__H
#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Core/graphics.h"
#include "../Systems/animation.h"
#include <iostream>

struct Player
{
    SDL_Texture *character = nullptr;
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *startTexture = nullptr;
    SDL_Texture *animationTexture = nullptr;
    SDL_Texture *jumpTexture = nullptr;
    SDL_Texture *attackTexture = nullptr;
    SDL_Rect rect;
    Animation animation;

    bool isMoving = false;
    bool wasMoving = false; // Lưu trạng thái di chuyển trước đó
    float movetime = 0.0f;  // Thời gian đã di chuyển
    bool isGrounded = false;
    float gravity = 1350.0f;  // Gia tốc trọng trường
    float jumpForce = 500.0f; // Lực nhảy
    float landTimer = 0.0f;
    static constexpr float PLATFORM_HEIGHT = 539.0f; // Change this value to whatever you want

    // Attack variables
    bool isAttacking = false;
    float attackTimer = 0.0f;
    float attackDuration = 0.5f; // Attack animation duration in seconds
    int attackFrame = 0;
    int attackDamage = 1;
    SDL_Rect attackHitbox;                                 // Hitbox for attack collision detection
    Animation::Direction lastDirection = Animation::RIGHT; // Lưu hướng trước khi tấn công

    // Biến cho animation ban đầu
    int startFrame = 0;
    float startFrameTime = 0.0f;

    // Biến cho immunity sau khi bị thương
    bool isImmune = false;
    float immuneTimer = 0.0f;
    float immuneDuration = 1.0f; // 1 giây bất khả xâm sau khi bị thương
    bool showPlayer = true;      // Để tạo hiệu ứng nhấp nháy khi bị thương
    float blinkTimer = 0.0f;

    // Debug
    bool enableDebug = true;
    bool justSpawned = true;
    bool hasFallen = false;
    bool justLanded = false;

    float x = 400;
    float y = 300;
    float velocityX;
    float velocityY;
    float speed = 100.0f;
    int width;
    int height;
    int health;

    // Method declarations
    void createPlayer(const Graphics &graphics);
    void spawnPlayer(Graphics &graphics, int spawnX, int spawnY);
    void jump();
    void update(float deltaTime);
    void render(SDL_Renderer *renderer, float deltaTime); // Added deltaTime parameter
    void movePlayer(Player &player, const Uint8 *currentKeyStates, float deltaTime, int level);
    void attack();
    void takeDamage();
    Player(SDL_Renderer *renderer);
    ~Player();
};
#endif