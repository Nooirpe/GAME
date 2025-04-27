#include "../../Headers/Entities/player.h"
#include "../../Headers/Systems/animation.h"

void Player::createPlayer(const Graphics &graphics)
{
    character = IMG_LoadTexture(graphics.renderer, "C:/C++/GAME/GAME/Assets/chibi/idle/idle.png");
    rect.h = height;
    rect.w = width;
}

void Player::spawnPlayer(Graphics &graphics, int spawnX, int spawnY)
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

    // Update attack state
    if (isAttacking)
    {
        attackTimer += deltaTime;

        const float totalAttackDuration = attackDuration;

        // End attack state when animation completes
        if (attackTimer >= totalAttackDuration)
        {
            isAttacking = false;
            attackTimer = 0.0f;
            attackFrame = 0;

            // Restore previous direction
            animation.setDirection(lastDirection);
        }
    }

    // Cập nhật vị trí dựa trên vận tốc
    x += velocityX * deltaTime;
    // Cập nhật hướng di chuyển cho animation
    if (!isAttacking) // Chỉ cập nhật hướng khi không tấn công
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

    // Xử lý animation - luôn cập nhật animation kể cả khi đang tấn công
    animation.update(deltaTime);
}

void Player::render(SDL_Renderer *renderer, float deltaTime)
{
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

void Player::movePlayer(Player &player, const Uint8 *currentKeyStates, float deltaTime, int level)
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

    // Handle attack input - can attack in any state, even while jumping
    if (currentKeyStates[SDL_SCANCODE_J] && !player.isAttacking)
    {
        player.attack();
    }

    // Level-specific movement logic
    if (level == 1)
    {
        // Kiểm tra nếu nhân vật đang ở trên hố
        bool isOverGap = ((player.x + player.width) > 432 && (player.x + player.width) < 480) || ((player.x + player.width) > 935 && (player.x + player.width) < 975);

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

        if (player.y >= PLATFORM_HEIGHT && player.y < PLATFORM_HEIGHT + 250)
        {
            // First gap boundaries
            if ((player.x + player.width) < 432)
            {
                player.x = 432 - player.width;
            }
            else if ((player.x + player.width > 480) && (player.x + player.width < 600))
            {
                player.x = 480 - player.width;
            }

            // Second gap boundaries
            else if ((player.x + player.width) < 935 && (player.x + player.width) > 800)
            {
                player.x = 935 - player.width;
            }
            else if ((player.x + player.width > 975))
            {
                player.x = 975 - player.width;
            }
        }

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
    else if (level == 2)
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
            if (player.x + player.width > 370 && player.x < 370)
            {
                player.x = 370 - player.width;
            }
        }

        // Platform 2 boundaries collision (430-460, height 71)
        if (player.y + player.height > PLATFORM_HEIGHT - 71 &&
            player.y < PLATFORM_HEIGHT - 71 + 71)
        {
            if (player.x + player.width > 430 && player.x < 430)
            {
                player.x = 430 - player.width;
            }
            if (player.x < 460 && player.x + player.width > 460)
            {
                player.x = 460;
            }
        }

        // Platform 3 boundaries collision (480-736, height 111)
        if (player.y + player.height > PLATFORM_HEIGHT - 111 &&
            player.y < PLATFORM_HEIGHT - 111 + 111)
        {
            if (player.x + player.width > 490 && player.x < 490)
            {
                player.x = 490 - player.width;
            }
            if (player.x < 736 && player.x + player.width > 736)
            {
                player.x = 736;
            }
        }

        // Platform 4 boundaries collision (811-860, height 52)
        if (player.y + player.height > PLATFORM_HEIGHT - 52 &&
            player.y < PLATFORM_HEIGHT - 52 + 52)
        {
            if (player.x + player.width > 811 && player.x + player.width < 811)
            {
                player.x = 811 - player.width;
            }
            if (player.x < 840 && player.x + player.width > 840)
            {
                player.x = 840;
            }
        }

        // Platform 5 boundaries collision (928-1015, height 16)
        if (player.y + player.height > PLATFORM_HEIGHT - 16 &&
            player.y < PLATFORM_HEIGHT - 16 + 16)
        {
            if (player.x + player.width > 948 && player.x < 948)
            {
                player.x = 948 - player.width;
            }
            if (player.x < 995 && player.x + player.width > 995)
            {
                player.x = 995;
            }
        }
    }
    else if (level == 3)
    {
        if (!player.isGrounded)
        {
            // Increase falling speed (gravity effect)
            player.velocityY += player.gravity * deltaTime;

            // Update position based on velocity
            player.y += player.velocityY * deltaTime;
            // Check if player landed on platform
            if (player.y >= PLATFORM_HEIGHT + 13 - player.height)
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
        }
        // Update horizontal position
        player.x += player.velocityX * deltaTime;

        // Apply horizontal boundaries
        if (player.x < 0)
            player.x = 0;
        if (player.x > 1300 - player.width)
            player.x = 1300 - player.width;
    }

    // Set moving state based on any movement (horizontal or vertical)
    player.isMoving = (player.velocityX != 0 || !player.isGrounded);

    // Update collision rect
    player.rect.x = static_cast<int>(player.x);
    player.rect.y = static_cast<int>(player.y);

    // Update attack hitbox position based on player direction and position
    if (player.isAttacking)
    {
        if (player.animation.currentDirection == Animation::LEFT)
        {
            player.attackHitbox = {
                static_cast<int>(player.x - player.width / 2),
                static_cast<int>(player.y + player.height / 4),
                player.width / 2,
                player.height / 2};
        }
        else
        {
            player.attackHitbox = {
                static_cast<int>(player.x + player.width),
                static_cast<int>(player.y + player.height / 4),
                player.width / 2,
                player.height / 2};
        }
    }

    // Update animation
    player.animation.update(deltaTime);
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
