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

/**
 * @brief Tạo đối tượng Bat với các textures và thông số ban đầu
 *
 * @param graphics Đối tượng Graphics chứa renderer
 * @param startX Tọa độ x ban đầu
 * @param startY Tọa độ y ban đầu
 * @param leftBound Ranh giới bên trái mà Bat có thể di chuyển tới
 * @param rightBound Ranh giới bên phải mà Bat có thể di chuyển tới
 */
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

/**
 * @brief Phương thức riêng để tải textures
 *
 * @param renderer SDL_Renderer để tải textures
 */
void Bat::LoadTextures(SDL_Renderer *renderer)
{
    idleTexture = IMG_LoadTexture(renderer, "Assets/monster/Idle/Idle.png");
    flyTexture = IMG_LoadTexture(renderer, "Assets/monster/Fly/Fly.png");
    hurtTexture = IMG_LoadTexture(renderer, "Assets/monster/Hurt/Hurt.png");
    dieTexture = IMG_LoadTexture(renderer, "Assets/monster/Die/Die.png");
}

/**
 * @brief Tính toán kích thước của Bat dựa vào texture
 */
void Bat::CalculateDimensions()
{
    if (flyTexture)
    {
        int textureWidth, textureHeight;
        SDL_QueryTexture(flyTexture, NULL, NULL, &textureWidth, &textureHeight);
        int frameWidth = textureWidth / flyFrames;
        int frameHeight = textureHeight;
        float scale = 0.35f; // Scale để giảm kích thước so với texture gốc

        width = static_cast<int>(frameWidth * scale);
        height = static_cast<int>(frameHeight * scale);
    }
}

/**
 * @brief Cập nhật trạng thái của Bat trong mỗi frame
 *
 * @param deltaTime Thời gian giữa các frame
 * @param player Tham chiếu đến người chơi để tương tác
 */
void Bat::update(float deltaTime, const Player &player)
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

/**
 * @brief Xử lý chuyển động của Bat
 *
 * @param deltaTime Thời gian giữa các frame
 */
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

/**
 * @brief Xử lý va chạm với ranh giới di chuyển
 */
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

/**
 * @brief Cập nhật animation dựa theo trạng thái hiện tại
 *
 * @param deltaTime Thời gian giữa các frame
 */
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
        case IDLE:
            currentFrame = (currentFrame + 1) % idleFrames;
            break;

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

/**
 * @brief Đánh dấu Bat đã chết và bắt đầu animation chết
 */
void Bat::die()
{
    if (currentState != DIE && !isDead)
    {
        currentState = DIE;
        currentFrame = 0;
        frameTime = 0.0f;
    }
}

/**
 * @brief Xử lý khi Bat bị tấn công
 */
void Bat::hurt()
{
    // Chỉ xử lý nếu không đang trong trạng thái die hoặc hurt và chưa chết
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

/**
 * @brief Vẽ Bat lên màn hình
 *
 * @param renderer SDL_Renderer để vẽ
 */
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

    // Vẽ texture hiện tại
    RenderCurrentFrame(renderer, currentTexture, frameCount);
}

/**
 * @brief Vẽ frame hiện tại của sprite
 *
 * @param renderer SDL_Renderer để vẽ
 * @param texture Texture hiện tại
 * @param frameCount Tổng số frame của animation hiện tại
 */
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

/**
 * @brief Kiểm tra va chạm với người chơi và xử lý sát thương
 *
 * @param player Tham chiếu người chơi
 * @param renderer SDL_Renderer để vẽ debug hitbox (tuỳ chọn)
 * @return true nếu có va chạm, false nếu không
 */
bool Bat::collidesWithPlayer(const Player &player, SDL_Renderer *renderer)
{
    // Không thể va chạm nếu đã chết
    if (isDead)
        return false;

    // Không xử lý va chạm nếu người chơi đang miễn nhiễm sát thương
    if (player.isImmune)
        return false;

    // Tính toán hitbox thực tế (nhỏ hơn sprite để phù hợp hơn)
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

/**
 * @brief Tính toán hitbox thực tế của Bat (nhỏ hơn sprite)
 *
 * @return SDL_Rect Hitbox của Bat
 */
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

/**
 * @brief Tính toán hitbox thực tế của Player (nhỏ hơn sprite)
 *
 * @param player Tham chiếu đến Player
 * @return SDL_Rect Hitbox của Player
 */
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

/**
 * @brief Gây sát thương cho người chơi với hướng knockback phù hợp
 *
 * @param player Tham chiếu đến Player (const)
 */
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

/**
 * @brief Kiểm tra va chạm với hitbox tấn công của người chơi
 *
 * @param attackHitbox Hitbox tấn công để kiểm tra
 * @param renderer SDL_Renderer để vẽ debug hitbox (tuỳ chọn)
 * @return true nếu có va chạm, false nếu không
 */
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