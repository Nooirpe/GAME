#ifndef MOUSE_H
#define MOUSE_H
#include "../../src/include/SDL2/SDL.h"
#include "../Core/graphics.h"

/**
 * @struct Cursor
 * @brief Manages the custom mouse cursor display
 */
struct Cursor
{
    SDL_Texture *texCursor1, *texCursor2;
    SDL_Rect rect;
    SDL_Rect point;

    bool in = 0;

    /**
     * @brief Initializes the cursor with textures
     */
    void createCursor(const Graphics &graphics);

    /**
     * @brief Updates cursor position and state
     */
    void update();

    /**
     * @brief Renders the cursor on screen
     */
    void draw(const Graphics &graphics);
};

#endif
