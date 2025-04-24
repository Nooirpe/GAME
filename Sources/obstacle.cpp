#include "../Headers/obstacle.h"

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

    idleTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Idle/Idle.png");
    flyTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Fly/Fly.png");
    attackTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Attack/Attack.png");
    dieTexture = IMG_LoadTexture(graphics.renderer, "sdl_image/monster/Die/Die.png");

    int textureWidth, textureHeight;
    if (flyTexture)
    {
        SDL_QueryTexture(flyTexture, NULL, NULL, &textureWidth, &textureHeight);
        int frameWidth = textureWidth / flyFrames;
        int frameHeight = textureHeight;
        float scale = 0.5f;
        width = static_cast<int>(frameWidth * scale);
        height = static_cast<int>(frameHeight * scale);
    }

    rect = {static_cast<int>(x), static_cast<int>(y), width, height};
}

void Bat::update(float deltaTime, const Player &player)
{
    if (currentState == DIE)
    {
        updateAnimation(deltaTime);
        return;
    }

    float horizontalDistance = abs((x + width / 2) - (player.x + player.width / 2));
    float verticalDistance = abs((y + height / 2) - (player.y + player.height / 2));

    bool playerInRange = (horizontalDistance < 100 && verticalDistance < height);

    if (playerInRange && currentState != ATTACK && currentState != DIE)
    {
        currentState = ATTACK;
        currentFrame = 0;
        frameTime = 0.0f;
    }
    else if (currentState == ATTACK)
    {
        if (currentFrame >= attackFrames - 1 && frameTime >= frameDuration)
        {
            currentState = FLY;
            currentFrame = 0;
            frameTime = 0.0f;
        }
    }
    else
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
        case ATTACK:
            if (currentFrame < attackFrames - 1)
                currentFrame++;
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
    case ATTACK:
        currentTexture = attackTexture;
        frameCount = attackFrames;
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

    int batOffsetX = width * 0.2;
    int batOffsetY = height * 0.3;
    int playerOffsetX = player.width * 0.2;
    int playerOffsetY = player.height * 0.2;

    SDL_Rect batCollision = {static_cast<int>(x + batOffsetX), static_cast<int>(y + batOffsetY),
                             width - batOffsetX * 2, height - batOffsetY * 2};

    SDL_Rect playerCollision = {static_cast<int>(player.x + playerOffsetX), static_cast<int>(player.y + playerOffsetY),
                                player.width - playerOffsetX * 2, player.height - playerOffsetY * 2};

    return SDL_HasIntersection(&batCollision, &playerCollision);
}