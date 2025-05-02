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
 * @details The player character can move, jump, attack, and interact with platforms and enemies.
 *          It handles animations, physics, collisions, and state management.
 */
struct Player
{
    // Constants
    static constexpr float PLATFORM_HEIGHT = 539.0f;  /**< Standard platform height in the game */

    /**
     * @brief Constructor for Player class
     * @param renderer SDL_Renderer used to load textures
     */
    Player(SDL_Renderer *renderer);
    
    /**
     * @brief Destructor for Player class
     * @details Cleans up all allocated resources like textures
     */
    ~Player();

    // Core functions
    /**
     * @brief Creates the player character
     * @param graphics Graphics object containing the renderer
     */
    void createPlayer(const Graphics &graphics);
    
    /**
     * @brief Spawns the player at specified coordinates
     * @param graphics Graphics object containing the renderer
     * @param spawnX X-coordinate to spawn at
     * @param spawnY Y-coordinate to spawn at
     */
    void spawnPlayer(Graphics &graphics, int spawnX, int spawnY);
    
    /**
     * @brief Updates player state each frame
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void update(float deltaTime);
    
    /**
     * @brief Renders the player on screen
     * @param renderer SDL_Renderer to draw on
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void render(SDL_Renderer *renderer, float deltaTime);
    
    /**
     * @brief Handles player input for movement and actions
     * @param currentKeyStates Current keyboard state
     * @param deltaTime Time elapsed since last frame in seconds
     * @param level Current game level
     */
    void handleInput(const Uint8 *currentKeyStates, float deltaTime, int level);

    // Action functions
    /**
     * @brief Makes the player jump
     * @details Only works when player is on the ground
     */
    void jump();
    
    /**
     * @brief Makes the player attack
     * @details Creates an attack hitbox and triggers attack animation
     */
    void attack();
    
    /**
     * @brief Handles player taking damage and knockback
     * @param damageDirection Direction of damage source (0 = auto, 1 = right, -1 = left)
     */
    void takeDamage(int damageDirection = 0);

    // Physics functions
    /**
     * @brief Applies gravity to player
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void applyGravity(float deltaTime);
    
    /**
     * @brief Checks for collisions with platforms
     * @param level Current game level
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void checkPlatformCollisions(int level, float deltaTime);
    
    /**
     * @brief Applies horizontal movement to player
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void applyHorizontalMovement(float deltaTime);
    
    /**
     * @brief Checks and enforces level boundaries
     * @param level Current game level
     */
    void checkBoundaries(int level);

    // Basic elements
    float x = 400;                /**< Player's X position */
    float y = 300;                /**< Player's Y position */
    float velocityX = 0;          /**< Player's horizontal velocity */
    float velocityY = 0;          /**< Player's vertical velocity */
    float speed = 200.0f;         /**< Player's movement speed */
    int width = 64;               /**< Player's width */
    int height = 64;              /**< Player's height */
    int health = 5;               /**< Player's health points */
    SDL_Rect rect;                /**< Player's collision rectangle */

    // Movement states
    bool isMoving = false;        /**< Whether player is currently moving */
    bool wasMoving = false;       /**< Whether player was moving in the previous frame */
    float movetime = 0.0f;        /**< Time player has been moving */
    bool isGrounded = false;      /**< Whether player is on the ground */
    float gravity = 1350.0f;      /**< Gravity force applied to player */
    float jumpForce = 500.0f;     /**< Force applied when jumping */
    bool justSpawned = true;      /**< Whether player just spawned */
    bool hasFallen = false;       /**< Whether player has fallen off a platform */

    // Animation
    Animation animation;          /**< Animation controller */
    float landTimer = 0.0f;       /**< Timer for landing animation */
    bool justLanded = false;      /**< Whether player just landed */

    SDL_Texture *character = nullptr;       /**< Main character texture */
    SDL_Texture *idleTexture = nullptr;     /**< Idle animation texture */
    SDL_Texture *startTexture = nullptr;    /**< Jump start texture */
    SDL_Texture *animationTexture = nullptr;/**< Run animation texture */
    SDL_Texture *jumpTexture = nullptr;     /**< Jump landing texture */
    SDL_Texture *attackTexture = nullptr;   /**< Attack animation texture */

    // Animation frame counts
    static const int IDLE_FRAMES = 8;       /**< Number of frames in idle animation */
    static const int RUN_FRAMES = 7;        /**< Number of frames in run animation */
    static const int ATTACK_FRAMES = 8;     /**< Number of frames in attack animation */

    // Start animation
    int startFrame = 0;           /**< Current frame in start animation */
    float startFrameTime = 0.0f;  /**< Time in current start animation frame */

    // Attack states
    bool isAttacking = false;     /**< Whether player is attacking */
    float attackTimer = 0.0f;     /**< Timer for attack animation */
    float attackDuration = 0.8f;  /**< Duration of attack animation */
    int attackFrame = 0;          /**< Current frame in attack animation */
    int attackDamage = 1;         /**< Damage dealt by attack */
    SDL_Rect attackHitbox;        /**< Hitbox for attack collision detection */
    Animation::Direction lastDirection = Animation::RIGHT;  /**< Last direction player was facing */
    bool canAttackAgain = true;   /**< Whether player can attack again */

    // Damage states
    bool isImmune = false;        /**< Whether player is immune to damage */
    float immuneTimer = 0.0f;     /**< Timer for immunity duration */
    float immuneDuration = 1.0f;  /**< Duration of immunity after taking damage */
    bool showPlayer = true;       /**< Whether player is visible (for blinking effect) */
    float blinkTimer = 0.0f;      /**< Timer for blinking effect when immune */

    // Knockback states
    bool isKnockback = false;     /**< Whether player is in knockback state */
    float knockbackTimer = 0.0f;  /**< Timer for knockback duration */
    float knockbackDuration = 0.3f;  /**< Duration of knockback effect */
    float knockbackForceX = 300.0f;  /**< Horizontal force of knockback */
    float knockbackForceY = 200.0f;  /**< Vertical force of knockback */
    int knockbackDirection = 0;   /**< Direction of knockback (-1 = left, 1 = right) */

    // Debugging
    bool enableDebug = true;      /**< Whether debug visuals are enabled */

private:
    /**
     * @brief Updates attack state and animation
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void updateAttackState(float deltaTime);
    
    /**
     * @brief Updates immunity state and blinking effect
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void updateImmunityState(float deltaTime);
    
    /**
     * @brief Updates animation based on movement
     */
    void updateMovementAnimation();
    
    /**
     * @brief Updates knockback state and physics
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void updateKnockbackState(float deltaTime);
    
    /**
     * @brief Handles level one specific platform collisions
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void handleLevelOneCollisions(float deltaTime);
    
    /**
     * @brief Handles level two specific platform collisions
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void handleLevelTwoCollisions(float deltaTime);
    
    /**
     * @brief Handles level three specific platform collisions
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void handleLevelThreeCollisions(float deltaTime);
    
    /**
     * @brief Checks if player is landing on a platform
     * @param left Left edge of platform
     * @param right Right edge of platform
     * @param height Height of platform
     * @param tolerance Tolerance value for landing detection
     * @param deltaTime Time elapsed since last frame in seconds
     * @return True if player landed on the platform
     */
    bool checkPlatformLanding(float left, float right, float height, float tolerance, float deltaTime);
    
    /**
     * @brief Checks if player is on a specific platform
     * @param left Left edge of platform
     * @param right Right edge of platform
     * @param height Height of platform
     * @return True if player is on the platform
     */
    bool isOnPlatform(float left, float right, float height);
};
#endif