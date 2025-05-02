#ifndef _ANIMATION_H
#define _ANIMATION_H
#include <vector>
#include "../../src/include/SDL2/SDL.h"

/**
 * @class Animation
 * @brief Manages sprite animations with directional support
 */
class Animation
{
private:
    std::vector<SDL_Rect> frames;
    int currentFrame = 0;
    float frameTime = 0;
    float frameDelay = 0.1f;
    bool loop = true;
    bool debug = true;
    int framesPerDirection = 2;

public:
    /**
     * @enum Direction
     * @brief Possible directions for sprite animations
     */
    enum Direction
    {
        DOWN = 0,
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        IDLE = 4,
        ATTACK = 5
    };

    Direction currentDirection = IDLE;

    /**
     * @brief Constructor that initializes animation parameters
     */
    Animation(int spriteWidth, int spriteHeight, int numFrames, int framesPerDir = 2);

    /**
     * @brief Updates animation state based on time
     */
    void update(float deltaTime);

    /**
     * @brief Gets current frame for rendering
     */
    SDL_Rect getCurrentFrame();

    /**
     * @brief Gets offset for current direction
     */
    int getDirectionOffset();

    void setAnimationSpeed(float speed);

    /**
     * @brief Sets current animation direction
     */
    void setDirection(Direction dir);

    /**
     * @brief Gets current frame index
     */
    int getCurrentFrameIndex();
};

#endif