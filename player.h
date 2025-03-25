
#ifndef _PLAYER__H
#define _PLAYER__H
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL.h"
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL_image.h"
#include "graphics.h"
#include "animation.h"
#include <iostream>

class Player
{
private:
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *startTexture = nullptr;
    SDL_Texture *animationTexture = nullptr;
    Animation animation;
    bool isMoving = false;
    bool wasMoving = false; // Lưu trạng thái di chuyển trước đó
    float movetime = 0.0f;  // Thời gian đã di chuyển

    // Biến cho animation ban đầu
    int startFrame = 0;
    float startFrameTime = 0.0f;
    float startFrameDelay = 0.1f; // Mỗi frame tồn tại 0.1 giây

    // Debug
    bool enableDebug = true;

public:
    float x = 400;
    float y = 300;
    float velocityX;
    float velocityY;
    float speed = 200.0f;
    int width = 64;
    int height = 64;

    Player(SDL_Renderer *renderer) : animation(64, 64, 2, 1)
    {
        // Sử dụng đường dẫn nhất quán - đường dẫn tuyệt đối
        idleTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/New folder/player 1.PNG");
        if (idleTexture == nullptr)
        {
            std::cerr << "Failed to load idle texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        startTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/animation.png");
        if (startTexture == nullptr)
        {
            std::cerr << "Failed to load start texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        animationTexture = IMG_LoadTexture(renderer, "C:/C++/GAME/GAME/sdl_image/Animation2.png");
        if (animationTexture == nullptr)
        {
            std::cerr << "Failed to load animation texture! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        // Debug: In kích thước các textures
        int w, h;
        if (startTexture)
        {
            SDL_QueryTexture(startTexture, NULL, NULL, &w, &h);
            /*  std::cout << "Start texture dimensions: " << w << "x" << h << std::endl; */
        }
        if (animationTexture)
        {
            SDL_QueryTexture(animationTexture, NULL, NULL, &w, &h);
            /*         std::cout << "Animation texture dimensions: " << w << "x" << h << std::endl; */
        }

        animation.setAnimationSpeed(8.0f);
    }

    ~Player()
    {
        if (idleTexture != nullptr)
            SDL_DestroyTexture(idleTexture);
        if (startTexture != nullptr)
            SDL_DestroyTexture(startTexture);
        if (animationTexture != nullptr)
            SDL_DestroyTexture(animationTexture);
    }

    void update(float deltaTime)
    {
        // Lưu trạng thái di chuyển hiện tại
        wasMoving = isMoving;
        isMoving = (velocityX != 0 || velocityY != 0);

        // Cập nhật vị trí dựa trên vận tốc
        x += velocityX * deltaTime;
        y += velocityY * deltaTime;

        // Giữ nhân vật trong màn hình
        if (x < 0)
            x = 0;
        if (x > 800 - width)
            x = 800 - width;
        if (y < 0)
            y = 0;
        if (y > 600 - height)
            y = 600 - height;

        // Cập nhật hướng di chuyển cho animation
        if (velocityX > 0)
        {
            animation.setDirection(Animation::RIGHT);
        }
        else if (velocityX < 0)
        {
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

        // Xử lý thời gian di chuyển và animation
        if (isMoving)
        {
            // Nếu trước đó không di chuyển và bây giờ di chuyển
            if (!wasMoving)
            {
                movetime = 0.0f;
                startFrame = 0;
                startFrameTime = 0.0f;
                /*    if (enableDebug)
                   {
                       std::cout << "Started moving - reset timers" << std::endl;
                   } */
            }

            // Luôn tăng movetime khi đang di chuyển
            movetime += deltaTime;

            /*  if (enableDebug && (int)(movetime * 10) % 10 == 0)
             {
                 std::cout << "Moving: " << movetime << "s" << std::endl;
             } */

            // Xử lý animation ban đầu (trong 1 giây đầu)
            if (movetime <= 1.0f)
            {
                startFrameTime += deltaTime;
                if (startFrameTime >= startFrameDelay)
                {
                    startFrameTime = 0.0f;
                    startFrame = (startFrame + 1) % 2;
                    /*  if (enableDebug)
                     {
                         std::cout << "Start animation - Frame: " << startFrame << std::endl;
                     } */
                }
            }
            // Xử lý animation chính (sau 1 giây)
            else
            {
                animation.update(deltaTime);
                /* if (enableDebug && (int)(movetime * 10) % 30 == 0)
                {
                    std::cout << "Main animation - Frame: " << animation.getCurrentFrameIndex() << std::endl;
                } */
            }
        }
        else
        {
            // Reset các giá trị khi dừng
            movetime = 0.0f;
            startFrame = 0;
            startFrameTime = 0.0f;
        }
    }

    void render(SDL_Renderer *renderer)
    {
        SDL_Rect dstRect = {
            static_cast<int>(x),
            static_cast<int>(y),
            width,
            height};

        // DEBUG: Show current state

        // CASE 1: Not moving - show idle texture
        if (!isMoving)
        {
            if (idleTexture)
            {
                SDL_RenderCopy(renderer, idleTexture, nullptr, &dstRect);
                /* if (enableDebug)
                    std::cout << "Rendering: IDLE" << std::endl; */
            }
        }
        // CASE 2: Moving for less than 1 second - show start animation
        else if (movetime <= 1.0f)
        {
            if (startTexture)
            {
                // Create a source rectangle for the specific frame
                SDL_Rect srcRect = {
                    startFrame * width, // X offset based on current frame
                    0,                  // Y offset (top row)
                    width,              // Width of one frame
                    height              // Height of one frame
                };

                // Draw only the selected frame from the texture
                SDL_RenderCopy(renderer, startTexture, &srcRect, &dstRect);

                /* if (enableDebug)
                {
                    std::cout << "Rendering: START ANIMATION frame " << startFrame
                              << " (x=" << srcRect.x << ",y=" << srcRect.y
                              << ",w=" << srcRect.w << ",h=" << srcRect.h << ")"
                              << std::endl;
                } */
            }
        }
        // CASE 3: Moving for more than 1 second - show main animation
        else
        {
            if (animationTexture)
            {
                // Get the frame from the Animation class
                SDL_Rect animSrcRect = animation.getCurrentFrame();

                // Render the frame
                SDL_RenderCopy(renderer, animationTexture, &animSrcRect, &dstRect);

                /* if (enableDebug)
                {
                    std::cout << "Rendering main animation frame "
                              << animation.getCurrentFrameIndex()
                              << " direction=" << animation.getDirectionOffset() / 4
                              << " rect=(" << animSrcRect.x << "," << animSrcRect.y
                              << "," << animSrcRect.w << "," << animSrcRect.h << ")" << std::endl;
                } */
            }
        }

        // Visual debug indicator
        if (enableDebug)
        {
            // Draw a color bar showing the current state
            SDL_Rect statusBar = {
                static_cast<int>(x),
                static_cast<int>(y - 10),
                width,
                5};

            if (!isMoving)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            }
            else if (movetime <= 1.0f)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
                // Draw progress of initial animation
                statusBar.w = static_cast<int>((movetime / 1.0f) * width);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
            }

            SDL_RenderFillRect(renderer, &statusBar);
        }
    }
};
#endif