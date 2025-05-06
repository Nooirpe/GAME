#include "../../Headers/Entities/obstacle.h"

void Bat::createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound)
{
    // Khởi tạo vị trí và ranh giới
    x = startX;
    y = startY;
    leftBoundary = leftBound;
    rightBoundary = rightBound;
    hitCount = 0;

    // Tải textures
    LoadTextures(graphics.renderer);

    // Tính toán kích thước dựa vào texture
    CalculateDimensions();

    // Khởi tạo rect
    rect = {static_cast<int>(x), static_cast<int>(y), width, height};
}

void Bat::LoadTextures(SDL_Renderer *renderer)
{
    flyTexture = IMG_LoadTexture(renderer, "Assets/monster/Fly/Fly.png");
    hurtTexture = IMG_LoadTexture(renderer, "Assets/monster/Hurt/Hurt.png");
    dieTexture = IMG_LoadTexture(renderer, "Assets/monster/Die/Die.png");
}

void Bat::CalculateDimensions()
{
    if (flyTexture)
    {
        int textureWidth, textureHeight;
        SDL_QueryTexture(flyTexture, NULL, NULL, &textureWidth, &textureHeight);
        int frameWidth = textureWidth / flyFrames;
        int frameHeight = textureHeight;
        float scale = 0.25f; // Scale để giảm kích thước so với texture gốc

        width = static_cast<int>(frameWidth * scale);
        height = static_cast<int>(frameHeight * scale);
    }
}

void Bat::update(float deltaTime)
{
    // Nếu đã chết, chỉ cập nhật animation
    if (currentState == DIE)
    {
        updateAnimation(deltaTime);
        return;
    }

    // Xử lý chuyển động
    UpdateMovement(deltaTime);

    // Cập nhật hit box
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);

    // Cập nhật animation
    updateAnimation(deltaTime);
}

void Bat::UpdateMovement(float deltaTime)
{
    // Nếu đang bị thương, không di chuyển
    if (currentState == HURT)
        return;

    // Thay đổi trạng thái về FLY
    currentState = FLY;

    // Di chuyển theo hướng hiện tại
    x += direction * speed * deltaTime;

    // Xử lý va chạm với ranh giới
    HandleBoundaryCollisions();
}

void Bat::HandleBoundaryCollisions()
{
    if (x <= leftBoundary)
    {
        x = leftBoundary;
        direction = 1; // Đổi hướng sang phải
    }
    else if (x + width >= rightBoundary)
    {
        x = rightBoundary - width;
        direction = -1; // Đổi hướng sang trái
    }
}

void Bat::updateAnimation(float deltaTime)
{
    frameTime += deltaTime;

    // Chỉ cập nhật frame khi đã đủ thời gian
    if (frameTime >= frameDuration)
    {
        frameTime = 0.0f;

        // Xử lý animation theo từng trạng thái
        switch (currentState)
        {
        case FLY:
            currentFrame = (currentFrame + 1) % flyFrames;
            break;

        case HURT:
            // Animation hurt tiến từng frame một
            if (currentFrame < hurtFrames - 1)
                currentFrame++;
            else
            {
                // Khi animation hurt hoàn thành, trở về trạng thái FLY
                currentState = FLY;
                currentFrame = 0;
            }
            break;

        case DIE:
            // Animation die tiến từng frame một
            if (currentFrame < dieFrames - 1)
                currentFrame++;
            else
                isDead = true; // Khi animation kết thúc, đánh dấu đã chết hoàn toàn
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
        frameTime = 0.0f;
    }
}

void Bat::hurt()
{
    // Chỉ xử lý nếu không đang trong trạng thái die hợac hurt
    if (currentState != DIE && currentState != HURT && !isDead)
    {
        hitCount++;

        if (hitCount == 1)
        {
            // Lần đầu bị đánh - chuyển sang trạng thái HURT
            currentState = HURT;
            currentFrame = 0;
            frameTime = 0.0f;
            hurtTimer = 0.0f;
        }
        else if (hitCount >= 2)
        {
            // Lần thứ hai bị đánh - chuyển sang trạng thái DIE
            currentState = DIE;
            currentFrame = 0;
            frameTime = 0.0f;
        }
    }
}

void Bat::render(SDL_Renderer *renderer)
{
    // Nếu đã chết hoàn toàn thì không vẽ gì
    if (isDead)
        return;

    // Chọn texture và số lượng frame phù hợp với trạng thái hiện tại
    SDL_Texture *currentTexture = nullptr;
    int frameCount = 0;

    switch (currentState)
    {
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

    // Vẽ texture hiện tại
    RenderCurrentFrame(renderer, currentTexture, frameCount);
}

void Bat::RenderCurrentFrame(SDL_Renderer *renderer, SDL_Texture *texture, int frameCount)
{
    if (!texture)
        return;

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    int sourceFrameWidth = textureWidth / frameCount;
    int sourceFrameHeight = textureHeight;

    // Tạo source rect từ sprite sheet
    SDL_Rect srcRect = {
        currentFrame * sourceFrameWidth,
        0,
        sourceFrameWidth,
        sourceFrameHeight};

    // Tạo destination rect tại vị trí của Bat
    SDL_Rect destRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        width,
        height};

    // Xác định flip dựa vào hướng di chuyển
    SDL_RendererFlip flip = (direction < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Vẽ frame hiện tại
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
}

bool Bat::collidesWithPlayer(const Player &player)
{
    // Không thể va chạm nếu đã chết
    if (isDead)
        return false;

    // Không xử lý va chạm nếu người chơi đang miễn nhiễm sát thương
    if (player.isImmune)
        return false;

    // Tính toán hitbox thực tế
    SDL_Rect batCollision = CalculateBatHitbox();
    SDL_Rect playerCollision = CalculatePlayerHitbox(player);

    // Kiểm tra va chạm giữa hai hitbox
    if (SDL_HasIntersection(&batCollision, &playerCollision))
    {
        // Xác định hướng knockback và gây sát thương cho người chơi
        ApplyDamageToPlayer(player);
        return true;
    }

    return false;
}

SDL_Rect Bat::CalculateBatHitbox()
{
    int batOffsetX = width * 0.2;
    int batOffsetY = height * 0.3;

    return {
        static_cast<int>(x + batOffsetX),
        static_cast<int>(y + batOffsetY),
        width - batOffsetX * 2,
        height - batOffsetY * 2};
}

SDL_Rect Bat::CalculatePlayerHitbox(const Player &player)
{
    int playerOffsetX = player.width * 0.2;
    int playerOffsetY = player.height * 0.2;

    return {
        static_cast<int>(player.x + playerOffsetX),
        static_cast<int>(player.y + playerOffsetY),
        player.width - playerOffsetX * 2,
        player.height - playerOffsetY * 2};
}

void Bat::ApplyDamageToPlayer(const Player &player)
{
    // Xác định hướng knockback dựa vào vị trí của Bat và người chơi
    int knockbackDirection;

    // Nếu Bat ở bên phải người chơi, đẩy người chơi sang trái
    if (x > player.x)
        knockbackDirection = 1;
    // Nếu Bat ở bên trái người chơi, đẩy người chơi sang phải
    else
        knockbackDirection = -1;

    // Áp dụng sát thương và knockback vào người chơi
    Player *mutablePlayer = const_cast<Player *>(&player);
    mutablePlayer->takeDamage(knockbackDirection);
}

bool Bat::checkAttackCollision(const SDL_Rect &attackHitbox, SDL_Renderer *renderer)
{

    if (isDead)
        return false;

    // Tính toán hitbox thực tế của Bat
    SDL_Rect batCollision = CalculateBatHitbox();

    // Vẽ hitbox debug nếu cần
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100); // Màu xanh lá
        SDL_RenderDrawRect(renderer, &batCollision);
    }

    // Kiểm tra va chạm giữa hitbox của Bat và hitbox tấn công
    return SDL_HasIntersection(&batCollision, &attackHitbox);
}