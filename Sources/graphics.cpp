#include "../Headers/graphics.h"
#include <iostream>

void Graphics::logErrorAndExit(const char *msg, const char *error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_ShowCursor(0);
}

void Graphics::prepareImg(SDL_Texture *background)
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::prepareScene(SDL_Texture *background)
{
    if (background != nullptr)
        SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Graphics::loadTexture(const char *filename)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;
    SDL_RenderCopy(renderer, texture, src, &dest);
}

void Graphics::quit()
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::render(const ScrollingBackground &background)
{
    renderTexture(background.texture, background.scrollingOffset, 0);
    renderTexture(background.texture, background.scrollingOffset - background.width, 0);
}

Mix_Music *Graphics::loadMusic(const char *path)
{
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void Graphics::play(Mix_Music *gMusic)
{
    if (gMusic == nullptr)
        return;

    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
}

Mix_Chunk *Graphics::loadSound(const char *path)
{
    Mix_Chunk *gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return gChunk;
}

void Graphics::play(Mix_Chunk *sound, bool sfxEnabled)
{
    if (sfxEnabled && sound != nullptr)
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}