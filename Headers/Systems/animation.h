#ifndef _ANIMATION_H
#define _ANIMATION_H
#include <vector>
#include "../../src/include/SDL2/SDL.h"

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
    enum Direction
    {
        DOWN = 0,
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        IDLE = 4
    };

    Direction currentDirection = IDLE;

    Animation(int spriteWidth, int spriteHeight, int numFrames, int numRows, int framesPerDir = 2);
    void update(float deltaTime);
    SDL_Rect getCurrentFrame();
    int getDirectionOffset();
    void setAnimationSpeed(float speed);
    void setDirection(Direction dir);
    int getCurrentFrameIndex();
};

#endif