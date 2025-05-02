#include "../../Headers/Entities/obstacle.h"

void Bat::spawnBat(float spawnX, float spawnY, float leftBound, float rightBound)
{
    x = spawnX;
    y = spawnY;
    leftBoundary = leftBound;
    rightBoundary = rightBound;
    direction = 1;
    currentFrame = 0;
    frameTime = 0.0f;
    currentState = FLY;
    rect = {static_cast<int>(x), static_cast<int>(y), width, height};
    isDead = false;
}

void Bat::createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound)
{
    x = startX;
    y = startY;
    leftBoundary = leftBound;
    rightBoundary = rightBound;
    hitCount = 0; // Khởi tạo số lần bị đánh là 0

    idleTexture = IMG_LoadTexture(graphics.renderer, "Assets/monster/Idle/Idle.png");
    flyTexture = IMG_LoadTexture(graphics.renderer, "Assets/monster/Fly/Fly.png");
    hurtTexture = IMG_LoadTexture(graphics.renderer, "Assets/monster/Hurt/Hurt.png");
    dieTexture = IMG_LoadTexture(graphics.renderer, "Assets/monster/Die/Die.png");

    int textureWidth, textureHeight;
    if (flyTexture)
    {
        SDL_QueryTexture(flyTexture, NULL, NULL, &textureWidth, &textureHeight);
        int frameWidth = textureWidth / flyFrames;
        int frameHeight = textureHeight;
        float scale = 0.35f; // Giảm kích thước bat (từ 0.5f xuống 0.35f)
        width = static_cast<int>(frameWidth * scale);
        height = static_cast<int>(frameHeight * scale);
    }

    rect = {static_cast<int>(x), static_cast<int>(y), width, height};
}

void Bat::update(float deltaTime, const Player &player)
{
    // Nếu đang ở trạng thái DIE, chỉ cập nhật animation và không làm gì thêm
    if (currentState == DIE)
    {
        updateAnimation(deltaTime);
        return;
    }

    // Tiếp tục di chuyển qua lại nếu không ở trạng thái DIE hoặc HURT
    if (currentState != HURT)
    {
        currentState = FLY;
        x += direction * speed * deltaTime;
        if (x <= leftBoundary)
        {
            x = leftBoundary;
            direction = 1;
        }
        else if (x + width >= rightBoundary)
        {
            x = rightBoundary - width;
            direction = -1;
        }
    }

    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    updateAnimation(deltaTime);
}

void Bat::updateAnimation(float deltaTime)
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
        case HURT:
            // Handle hurt animation just like die animation
            if (currentFrame < hurtFrames - 1)
                currentFrame++;
            else
            {
                // When hurt animation completes, return to FLY state
                currentState = FLY;
                currentFrame = 0;
            }
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

void Bat::die()
{
    if (currentState != DIE && !isDead)
    {
        currentState = DIE;
        currentFrame = 0;
        frameTime = 0;
    }
}

void Bat::hurt()
{
    if (currentState != DIE && currentState != HURT && !isDead)
    {
        hitCount++;

        if (hitCount == 1)
        {
            // Lần đầu bị đánh - chuyển sang trạng thái HURT
            currentState = HURT;
            currentFrame = 0;
            frameTime = 0;
            hurtTimer = 0.0f;
        }
        else if (hitCount >= 2)
        {
            // Lần thứ hai bị đánh - chuyển sang trạng thái DIE
            currentState = DIE;
            currentFrame = 0;
            frameTime = 0;
        }
    }
}

void Bat::render(SDL_Renderer *renderer)
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
    case HURT:
        currentTexture = hurtTexture;
        frameCount = hurtFrames;
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
        SDL_Rect srcRect = {currentFrame * sourceFrameWidth, 0, sourceFrameWidth, sourceFrameHeight};
        SDL_Rect destRect = {static_cast<int>(x), static_cast<int>(y), width, height};
        SDL_RendererFlip flip = (direction < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &destRect, 0, NULL, flip);
    }
}

bool Bat::collidesWithPlayer(const Player &player, SDL_Renderer *renderer)
{
    if (isDead)
        return false;

    // Skip collision if player is already immune
    if (player.isImmune)
        return false;

    int batOffsetX = width * 0.2;
    int batOffsetY = height * 0.3;
    int playerOffsetX = player.width * 0.2;
    int playerOffsetY = player.height * 0.2;

    SDL_Rect batCollision = {static_cast<int>(x + batOffsetX), static_cast<int>(y + batOffsetY),
                             width - batOffsetX * 2, height - batOffsetY * 2};

    SDL_Rect playerCollision = {static_cast<int>(player.x + playerOffsetX), static_cast<int>(player.y + playerOffsetY),
                                player.width - playerOffsetX * 2, player.height - playerOffsetY * 2};

    // Kiểm tra xem có va chạm không
    if (SDL_HasIntersection(&batCollision, &playerCollision))
    {
        // Xác định hướng knockback dựa vào vị trí tương đối của quái vật và người chơi
        int knockbackDirection = 0;

        // Nếu quái vật ở bên phải người chơi, đẩy người chơi về bên trái
        if (x > player.x)
            knockbackDirection = 1; // Đẩy người chơi sang trái
        // Nếu quái vật ở bên trái người chơi, đẩy người chơi về bên phải
        else
            knockbackDirection = -1; // Đẩy người chơi sang phải

        // Áp dụng sát thương và knockback vào người chơi với hướng đúng
        Player *mutablePlayer = const_cast<Player *>(&player);
        mutablePlayer->takeDamage(knockbackDirection);

        return true;
    }

    return false;
}

bool Bat::checkAttackCollision(const SDL_Rect &attackHitbox, SDL_Renderer *renderer)
{
    if (isDead)
        return false;

    // Hitbox của bat
    int batOffsetX = width * 0.2;
    int batOffsetY = height * 0.3;

    SDL_Rect batCollision = {
        static_cast<int>(x + batOffsetX),
        static_cast<int>(y + batOffsetY),
        width - batOffsetX * 2,
        height - batOffsetY * 2};

    // Vẽ hitbox
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100); // Màu xanh lá cho hitbox bat
        SDL_RenderDrawRect(renderer, &batCollision);
    }

    // Kiểm tra va chạm giữa hitbox của bat và hitbox tấn công
    bool hasCollision = SDL_HasIntersection(&batCollision, &attackHitbox);

    return hasCollision;
}