#ifndef _OBSTACLE__H
#define _OBSTACLE__H
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL.h"
#include "C:/C++/GAME/GAME/src/include/SDL2/SDL_image.h"
#include "graphics.h"
#include <bits/stdc++.h>
#include "player.h"
#include "animation.h"
using namespace std;

struct Bat
{
    SDL_Texture *idleTexture = nullptr;
    SDL_Texture *flyTexture = nullptr;
    SDL_Texture *attackTexture = nullptr;
    SDL_Texture *dieTexture = nullptr;

    float x = 0.0f;
    float y = 0.0f;
    float speed = 100.0f;

    int width = 64;
    int height = 64;

    float leftBoundary = 500.0f;
    float rightBoundary = 600.0f;

    int direction = 1;

    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.1f;

    int idleFrames = 12;
    int flyFrames = 8;
    int attackFrames = 8;
    int dieFrames = 8;

    enum State
    {
        IDLE,
        FLY,
        ATTACK,
        DIE
    };
    State currentState = FLY;
    bool isDead = false;
    SDL_Rect rect;

    void spawnBat(float spawnX, float spawnY, float leftBound, float rightBound);
    void createBat(const Graphics &graphics, float startX, float startY, float leftBound, float rightBound);
    void update(float deltaTime, const Player &player);
    void updateAnimation(float deltaTime);
    void die();
    void render(SDL_Renderer *renderer);
    bool collidesWithPlayer(const Player &player, SDL_Renderer *renderer = nullptr);
};

#endif