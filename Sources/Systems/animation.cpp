#include "../../Headers/Systems/animation.h"
#include <iostream>

Animation::Animation(int spriteWidth, int spriteHeight, int numFrames, int framesPerDir)
{
    framesPerDirection = framesPerDir;
    for (int i = 0; i < numFrames; i++)
    {
        SDL_Rect frame = {
            i * spriteWidth,
            0,
            spriteWidth,
            spriteHeight};
        frames.push_back(frame);
    }
}

void Animation::update(float deltaTime)
{
    frameTime += deltaTime;

    if (frameTime >= frameDelay)
    {
        frameTime = 0;
        currentFrame++;

        if (currentFrame >= framesPerDirection)
        {
            if (loop)
            {
                currentFrame = 0;
            }
            else
            {
                currentFrame = framesPerDirection - 1;
            }
        }
    }
}

void Animation::setAnimationSpeed(float speed)
{
    frameDelay = 1.0f / speed;
}

void Animation::setDirection(Direction dir)
{
    if (currentDirection != dir)
    {
        currentFrame = 0;
        frameTime = 0;
    }
    currentDirection = dir;
}