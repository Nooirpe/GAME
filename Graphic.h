#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct graphic{
    SDL_Window *window;
    SDL_Renderer *renderer;
    void logExitAndError(const char* msg, const char error){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR, "%s :%s", msg, error);
        SDL_Quit();
    }
    void init(){
        if(SDL_INIT_EVERYTHING != 0)
            logExitAndError("SDL_Init", SDL_GetError());
        window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window == nullptr) logExitAndError("CreateWindow",SDL_GetError());
        
    }
};
#endif