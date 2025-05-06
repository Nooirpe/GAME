#include "../../Headers/Entities/player.h"
#include "../../Headers/Systems/animation.h"

void Player::spawnPlayer(int spawnX, int spawnY)
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

void Player::jump()
{
    if (isGrounded)
    {
        velocityY = -jumpForce;
        isGrounded = false;
        justLanded = false;
    }
}

Player::Player(SDL_Renderer *renderer) : animation(64, 64, 2, 1)
{
    health = 5;
    idleTexture = IMG_LoadTexture(renderer, "Assets/chibi/idle/idle.png");
    if (idleTexture == nullptr)
    {
        std::cerr << "Failed to load idle texture! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    animationTexture = IMG_LoadTexture(renderer, "Assets/chibi/run/run.png");
    if (animationTexture == nullptr)
    {
        std::cerr << "Failed to load run texture! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    startTexture = IMG_LoadTexture(renderer, "Assets/chibi/jump/jump.png");
    if (startTexture == nullptr)
    {
        std::cerr << "Failed to load jump texture! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    jumpTexture = IMG_LoadTexture(renderer, "Assets/chibi/jump/jump 1.png");
    if (jumpTexture == nullptr)
    {
        std::cerr << "Failed to load landing texture! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    attackTexture = IMG_LoadTexture(renderer, "Assets/chibi/attack/attack.png");
    if (attackTexture == nullptr)
    {
        std::cerr << "Failed to load attack texture! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    animation.setAnimationSpeed(8.0f);
}

Player::~Player()
{
    if (idleTexture != nullptr)
        SDL_DestroyTexture(idleTexture);
    if (startTexture != nullptr)
        SDL_DestroyTexture(startTexture);
    if (animationTexture != nullptr)
        SDL_DestroyTexture(animationTexture);
    if (jumpTexture != nullptr)
        SDL_DestroyTexture(jumpTexture);
    if (attackTexture != nullptr)
        SDL_DestroyTexture(attackTexture);
}

void Player::update(float deltaTime)
{
    // Lưu trạng thái di chuyển hiện tại
    wasMoving = isMoving;
    isMoving = (velocityX != 0 || velocityY != 0);

    // Update specific states in order
    updateAttackState(deltaTime);
    updateImmunityState(deltaTime);
    updateMovementAnimation();
    updateKnockbackState(deltaTime);

    // Update animation system
    animation.update(deltaTime);
}

void Player::updateAttackState(float deltaTime)
{
    if (isAttacking)
    {
        attackTimer += deltaTime;

        // End attack state when animation completes
        if (attackTimer >= attackDuration)
        {
            isAttacking = false;
            attackTimer = 0.0f;
            attackFrame = 0;

            // Restore previous direction
            animation.setDirection(lastDirection);
        }
    }
}

void Player::updateImmunityState(float deltaTime)
{
    if (isImmune)
    {
        immuneTimer += deltaTime;
        blinkTimer += deltaTime;

        // Create blinking effect
        if (blinkTimer >= 0.1f)
        {
            showPlayer = !showPlayer;
            blinkTimer = 0.0f;
        }

        // End immunity state when timer expires
        if (immuneTimer >= immuneDuration)
        {
            isImmune = false;
            showPlayer = true;
        }
    }
}

void Player::updateMovementAnimation()
{
    if (velocityX > 0)
    {
        lastDirection = Animation::RIGHT;
        animation.setDirection(Animation::RIGHT);
    }
    else if (velocityX < 0)
    {
        lastDirection = Animation::LEFT;
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
}

void Player::render(SDL_Renderer *renderer, float deltaTime)
{
    // Always update attack state in render to ensure it gets called every frame
    updateAttackState(deltaTime);

    // Nếu đang trong trạng thái bất khả xâm và đang ở giai đoạn ẩn của hiệu ứng nhấp nháy
    if (isImmune && !showPlayer)
    {
        return; // Không vẽ nhân vật
    }

    SDL_Rect dstRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        width,
        height};

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    // Xác định hướng quay mặt của nhân vật
    if (animation.currentDirection == Animation::LEFT || lastDirection == Animation::LEFT)
        flip = SDL_FLIP_NONE;
    else
        flip = SDL_FLIP_HORIZONTAL;

    // CASE 0: Attacking - show attack animation
    if (isAttacking)
    {
        if (attackTexture)
        {
            int texW, texH;
            SDL_QueryTexture(attackTexture, NULL, NULL, &texW, &texH);
            int frameCount = 8; // 8 frames attack
            int frameWidth = texW / frameCount;

            float animationProgress;
            int attackDisplayFrame;

            if (attackTimer < 0.01f)
            {
                // Force the first frame to appear instantly when attack starts
                attackDisplayFrame = 0;
            }
            else
            {
                // Normal animation progression
                animationProgress = attackTimer / attackDuration;

                // Ensure animation progress stays within valid range (0.0-1.0)
                if (animationProgress > 1.0f)
                    animationProgress = 1.0f;

                // Calculate the current frame based on progress
                attackDisplayFrame = static_cast<int>(animationProgress * frameCount);

                // Prevent index out of bounds
                if (attackDisplayFrame >= frameCount)
                    attackDisplayFrame = frameCount - 1;
            }

            SDL_Rect srcRect = {
                attackDisplayFrame * frameWidth,
                0,
                frameWidth,
                texH};

            SDL_RenderCopyEx(renderer, attackTexture, &srcRect, &dstRect, 0, NULL, flip);

            // Hiển thị hitbox nếu debug mode được bật
            if (enableDebug)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
                SDL_RenderFillRect(renderer, &attackHitbox);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
    }
    // CASE 1: Just landed - show landing texture
    else if (justLanded)
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
    // CASE 2: Idle - show idle animation
    else if (!isMoving && isGrounded)
    {
        if (idleTexture)
        {
            int texW, texH;
            SDL_QueryTexture(idleTexture, NULL, NULL, &texW, &texH);
            int frameWidth = texW / 8; // 8 frames in idle animation

            int idleFrame = (SDL_GetTicks() / 100) % 8;
            SDL_Rect srcRect = {
                idleFrame * frameWidth,
                0,
                frameWidth,
                texH};

            SDL_RenderCopyEx(renderer, idleTexture, &srcRect, &dstRect, 0, NULL, flip);
        }
    }
    // CASE 3: In the air - show jump animation
    else if (!isGrounded)
    {
        if (startTexture)
        {
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
                runFrame * frameWidth,
                0,
                frameWidth,
                texH};

            SDL_RenderCopyEx(renderer, animationTexture, &srcRect, &dstRect, 0, NULL, flip);
        }
    }
}

void Player::attack()
{
    if (!isAttacking)
    {
        isAttacking = true;
        attackTimer = 0.0f; // Start exactly at 0 for immediate animation start
        attackFrame = 0;    // Reset frame index

        // Lưu hướng hiện tại trước khi tấn công
        if (animation.currentDirection == Animation::LEFT || animation.currentDirection == Animation::RIGHT)
            lastDirection = animation.currentDirection;

        if (lastDirection == Animation::LEFT)
        {
            // Attack hitbox to the left
            attackHitbox = {
                static_cast<int>(x - width / 2),
                static_cast<int>(y + height / 4),
                width / 2, // Hitbox width
                height / 2 // Hitbox height
            };
        }
        else
        {
            // Attack hitbox to the right
            attackHitbox = {
                static_cast<int>(x + width),
                static_cast<int>(y + height / 4),
                width / 2, // Hitbox width
                height / 2 // Hitbox height
            };
        }
    }
}

void Player::takeDamage(int damageDirection)
{
    if (!isImmune)
    {
        health--;
        isImmune = true;
        immuneTimer = 0.0f;
        showPlayer = true;
        blinkTimer = 0.0f;

        // Activate knockback effect
        isKnockback = true;
        knockbackTimer = 0.0f;

        // Set knockback direction based on parameter or player facing direction
        if (damageDirection != 0)
        {
            // Use specified direction
            knockbackDirection = -damageDirection; // Reverse to push away
        }
        else
        {
            // Determine direction based on player facing direction
            if (lastDirection == Animation::RIGHT)
                knockbackDirection = -1; // Knock back to the left
            else
                knockbackDirection = 1; // Knock back to the right
        }
    }
}

void Player::handleInput(const Uint8 *currentKeyStates, float deltaTime, int level)
{
    // Only allow player control if not in knockback state
    if (!isKnockback)
    {
        velocityX = 0;

        // Handle horizontal movement
        if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
        {
            velocityX = -speed;
            animation.currentDirection = Animation::LEFT;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
        {
            velocityX = speed;
            animation.currentDirection = Animation::RIGHT;
        }

        // Handle jump input - only when player is on the ground
        if ((currentKeyStates[SDL_SCANCODE_SPACE] || currentKeyStates[SDL_SCANCODE_UP] ||
             currentKeyStates[SDL_SCANCODE_W]) &&
            isGrounded)
        {
            jump();
            animation.currentDirection = Animation::UP;
        }

        // Handle attack input - can attack in any state, even while jumping
        if (currentKeyStates[SDL_SCANCODE_J] && !isAttacking)
        {
            attack();
        }
    }

    // Process physics for the current level
    applyGravity(deltaTime);
    checkPlatformCollisions(level);
    applyHorizontalMovement(deltaTime);
    checkBoundaries(level);
    // Update attack hitbox position based on player direction and position
    if (isAttacking)
    {
        if (lastDirection == Animation::LEFT)
        {
            attackHitbox = {
                static_cast<int>(x - width / 2),
                static_cast<int>(y + height / 4),
                width / 2,
                height / 2};
        }
        else
        {
            attackHitbox = {
                static_cast<int>(x + width),
                static_cast<int>(y + height / 4),
                width / 2,
                height / 2};
        }
    }
}

void Player::applyGravity(float deltaTime)
{
    if (!isGrounded)
    {
        // Increase falling speed (gravity effect)
        velocityY += gravity * deltaTime;

        // Update vertical position
        y += velocityY * deltaTime;
    }
}

void Player::applyHorizontalMovement(float deltaTime)
{
    // Update horizontal position
    x += velocityX * deltaTime;
}

bool Player::checkPlatformLanding(float left, float right, float platformHeight, float tolerance)
{
    // Check if player is above the platform
    if (x + width > left && x < right &&
        y + height <= PLATFORM_HEIGHT - platformHeight + tolerance + 3.0f &&
        y + height >= PLATFORM_HEIGHT - platformHeight - tolerance - 3.0f &&
        velocityY > 0) // Only land when falling down
    {
        // Land on platform
        y = PLATFORM_HEIGHT - height - platformHeight;
        velocityY = 0;
        isGrounded = true;
        justLanded = true;
        landTimer = 0.2f;

        if (velocityX == 0)
            animation.currentDirection = Animation::IDLE;

        return true;
    }

    return false;
}

bool Player::isOnPlatform(float left, float right, float platformHeight)
{
    return (x + width > left && x < right &&
            y + height == PLATFORM_HEIGHT - platformHeight);
}

void Player::checkPlatformCollisions(int level)
{
    if (level == 1)
    {
        handleLevelOneCollisions();
    }
    else if (level == 2)
    {
        handleLevelTwoCollisions();
    }
    else if (level == 3)
    {
        handleLevelThreeCollisions();
    }
}

void Player::handleLevelOneCollisions()
{
    // Check for gaps in level 1
    bool isOverGap = ((x + width) > 432 && (x + width) < 480) ||
                     ((x + width) > 935 && (x + width) < 975);

    // make the player not grounded when over a gap
    if (isOverGap)
    {
        isGrounded = false;

        if (y >= PLATFORM_HEIGHT - 10)
        {
            hasFallen = true;
        }
    }

    // Check if player landed on main platform
    if (!isGrounded)
    {
        if (y >= PLATFORM_HEIGHT + 13 - height && !isOverGap && !hasFallen)
        {
            y = PLATFORM_HEIGHT + 13 - height;
            velocityY = 0;
            isGrounded = true;
            justLanded = true;
            landTimer = 0.2f;

            if (velocityX == 0)
                animation.currentDirection = Animation::IDLE;
        }

        // Limit maximum fall depth
        if (y > 730 && isOverGap)
        {
            y = 730;
        }
    }
}

void Player::handleLevelTwoCollisions()
{
    if (!isGrounded)
    {
        // Check multiple platform landings using the helper function
        bool landed = false;

        // Platform 1: x from 350 to 406, height = 33
        landed |= checkPlatformLanding(350, 406, 33, 5);

        // Platform 2: x from 410 to 460, height = 71
        landed |= checkPlatformLanding(430, 460, 71, 5);

        // Platform 3: x from 465 to 736, height = 111
        landed |= checkPlatformLanding(480, 736, 111, 5);

        // Platform 4: x from 811 to 860, height = 52
        landed |= checkPlatformLanding(811, 860, 52, 5);

        // Platform 5: x from 928 to 1015, height = 16
        landed |= checkPlatformLanding(948, 995, 16, 5);

        // Main platform
        if (!landed && y >= PLATFORM_HEIGHT + 13 - height && velocityY > 0)
        {
            y = PLATFORM_HEIGHT + 13 - height;
            velocityY = 0;
            isGrounded = true;
            justLanded = true;
            landTimer = 0.2f;

            if (velocityX == 0)
                animation.currentDirection = Animation::IDLE;
        }
    }
    else // Player is grounded - check if still on platform
    {
        bool stillOnPlatform =
            isOnPlatform(350, 406, 33) ||       // Platform 1
            isOnPlatform(430, 460, 71) ||       // Platform 2
            isOnPlatform(480, 736, 111) ||      // Platform 3
            isOnPlatform(811, 860, 52) ||       // Platform 4
            isOnPlatform(948, 995, 16) ||       // Platform 5
            y + height == PLATFORM_HEIGHT + 13; // Main floor

        if (!stillOnPlatform)
        {
            isGrounded = false;
        }
    }
}

void Player::handleLevelThreeCollisions()
{
    if (!isGrounded)
    {
        // Check multiple platform landings using the helper function
        bool landed = false;

        // Platform 1: x from 367 to 616, height = 57
        landed |= checkPlatformLanding(375, 600, 57, 5);

        // Platform 2: x from 618 to 913, height = 121
        landed |= checkPlatformLanding(630, 900, 121, 5);

        // Main platform
        if (!landed && y >= PLATFORM_HEIGHT + 13 - height && velocityY > 0)
        {
            y = PLATFORM_HEIGHT + 13 - height;
            velocityY = 0;
            isGrounded = true;
            justLanded = true;
            landTimer = 0.2f;

            if (velocityX == 0)
                animation.currentDirection = Animation::IDLE;
        }
    }
    else // Player is grounded - check if still on platform
    {
        bool stillOnPlatform =
            isOnPlatform(375, 600, 57) ||       // Platform 1
            isOnPlatform(630, 900, 121) ||      // Platform 2
            y + height == PLATFORM_HEIGHT + 13; // Main floor

        if (!stillOnPlatform)
        {
            isGrounded = false;
        }
    }
}

void Player::checkBoundaries(int level)
{
    // Basic horizontal boundaries for all levels
    if (x < 0)
        x = 0;
    if (x > 1300 - width)
        x = 1300 - width;

    // Level-specific boundaries
    if (level == 1)
    {
        if (y >= PLATFORM_HEIGHT && y < PLATFORM_HEIGHT + 250)
        {
            // First gap boundaries
            if ((x + width) < 432)
            {
                x = 432 - width;
            }
            else if ((x + width > 480) && (x + width < 600))
            {
                x = 480 - width;
            }

            // Second gap boundaries
            else if ((x + width) < 935 && (x + width) > 800)
            {
                x = 935 - width;
            }
            else if ((x + width > 975))
            {
                x = 975 - width;
            }
        }
    }
    else if (level == 2)
    {
        // Platform 1 boundaries collision (350-406, height 33)
        if (y + height > PLATFORM_HEIGHT - 33 && y < PLATFORM_HEIGHT - 33 + 33)
        {
            if (x + width > 370 && x < 370)
            {
                x = 370 - width;
            }
        }

        // Platform 2 boundaries collision (430-460, height 71)
        if (y + height > PLATFORM_HEIGHT - 71 && y < PLATFORM_HEIGHT - 71 + 71)
        {
            if (x + width > 430 && x < 430)
            {
                x = 430 - width;
            }
            if (x < 460 && x + width > 460)
            {
                x = 460;
            }
        }

        // Platform 3 boundaries collision (480-736, height 111)
        if (y + height > PLATFORM_HEIGHT - 111 && y < PLATFORM_HEIGHT - 111 + 111)
        {
            if (x + width > 490 && x < 490)
            {
                x = 490 - width;
            }
            if (x < 736 && x + width > 736)
            {
                x = 736;
            }
        }

        // Platform 4 boundaries collision (811-860, height 52)
        if (y + height > PLATFORM_HEIGHT - 52 && y < PLATFORM_HEIGHT - 52 + 52)
        {
            if (x + width > 811 && x < 811)
            {
                x = 811 - width;
            }
            if (x < 840 && x + width > 840)
            {
                x = 840;
            }
        }

        // Platform 5 boundaries collision (928-1015, height 16)
        if (y + height > PLATFORM_HEIGHT - 16 && y < PLATFORM_HEIGHT - 16 + 16)
        {
            if (x + width > 948 && x < 948)
            {
                x = 948 - width;
            }
            if (x < 995 && x + width > 995)
            {
                x = 995;
            }
        }
    }
    else if (level == 3)
    {
        // Platform 1 boundaries (375-600, height 57)
        if (y + height > PLATFORM_HEIGHT - 57 && y < PLATFORM_HEIGHT - 57 + 57)
        {
            if (x + width > 400 && x < 400)
            {
                x = 400 - width;
            }
        }

        // Platform 2 boundaries (630-900, height 121)
        if (y + height > PLATFORM_HEIGHT - 121 && y < PLATFORM_HEIGHT - 121 + 121)
        {
            if (x + width > 630 && x < 630)
            {
                x = 630 - width;
            }
            if (x < 900 && x + width > 900)
            {
                x = 900;
            }
        }
    }
}

void Player::updateKnockbackState(float deltaTime)
{
    if (isKnockback)
    {
        knockbackTimer += deltaTime;

        // Apply knockback forces
        velocityX = knockbackDirection * knockbackForceX;

        // Apply upward force if the player is on the ground
        if (isGrounded)
        {
            velocityY = -knockbackForceY;
            isGrounded = false;
        }

        // End knockback state when timer expires
        if (knockbackTimer >= knockbackDuration)
        {
            isKnockback = false;
            velocityX = 0;
        }
    }
}
