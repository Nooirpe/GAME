#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Systems/defs.h"
#include <vector>

/**
 * @struct Graphics
 * @brief Handles rendering and window management
 */
struct Graphics
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    /**
     * @brief Logs error message and exits the application
     */
    void logErrorAndExit(const char *msg, const char *error);

    /**
     * @brief Initializes the graphics system
     */
    void init();

    void prepareImg(SDL_Texture *background);

    void prepareScene(SDL_Texture *background = nullptr);

    void presentScene();

    /**
     * @brief Loads a texture from a file
     */
    SDL_Texture *loadTexture(const char *filename);

    /**
     * @brief Renders a texture at specified coordinates
     */
    void renderTexture(SDL_Texture *texture, int x, int y);

    /**
     * @brief Renders part of a texture using a source rectangle
     */
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

    /**
     * @brief Cleans up and shuts down the graphics system
     */
    void quit();
};

#endif // _GRAPHICS__H
