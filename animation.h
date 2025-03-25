#ifndef _ANIMATION_H
#define _ANIMATION_H
#include <vector>
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"

class Animation
{
private:
    std::vector<SDL_Rect> frames;
    int currentFrame = 0;
    float frameTime = 0;
    float frameDelay = 0.1f; // Thời gian giữa các frames
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

    Animation(int spriteWidth, int spriteHeight, int numFrames, int numRows, int framesPerDir = 2)
    {
        framesPerDirection = framesPerDir;
        // Tạo frames từ spritesheet
        for (int i = 0; i < numFrames; i++)
        {
            SDL_Rect frame = {
                i * spriteWidth,
                0,
                spriteWidth,
                spriteHeight};
            frames.push_back(frame);
        }

        /*   if (debug)
          {
              printf("Total frames: %zu\n", frames.size());
          } */
    }

    void update(float deltaTime)
    {
        frameTime += deltaTime;

        if (frameTime >= frameDelay)
        {
            frameTime = 0;
            currentFrame++;

            if (currentFrame >= framesPerDirection) // Chỉ sử dụng framesPerDirection frames cho mỗi hướng
            {
                if (loop)
                {
                    currentFrame = 0;
                    /*  if (debug)
                     {
                         printf("Animation loop back to frame 0\n");
                     } */
                }
                else
                {
                    currentFrame = framesPerDirection - 1; // Frame cuối của mỗi hướng
                }
            }

            /*  if (debug)
             {
                 printf("Animation frame updated to: %d\n", currentFrame);
             } */
        }
    }

    SDL_Rect getCurrentFrame()
    {
        if (currentFrame >= frames.size())
            currentFrame = 0;
        return frames[currentFrame];
    }

    int getDirectionOffset()
    {
        // Make sure we're using the right offset calculation
        return (currentDirection < IDLE) ? currentDirection * framesPerDirection : 0;
    }

    void setAnimationSpeed(float speed)
    {
        frameDelay = 1.0f / speed; // Frames trên giây
        /* if (debug)
        {
            printf("Animation speed set to: %.2f fps, frameDelay=%.4f\n", speed, frameDelay);
        } */
    }

    void setDirection(Direction dir)
    {
        // When direction changes, it's good to reset the frame counter
        if (currentDirection != dir)
        {
            currentFrame = 0;
            frameTime = 0;
        }
        currentDirection = dir;
    }

    int getCurrentFrameIndex()
    {
        return currentFrame;
    }
};

#endif