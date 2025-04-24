#define SDL_MAIN_HANDLED
#include <bits/stdc++.h>
#include "Headers/Core/GameEngine.h"

int main()
{
    // Create game engine instance
    GameEngine engine;

    // Initialize the game engine
    if (!engine.initialize())
    {
        std::cout << "Failed to initialize game engine!" << std::endl;
        return -1;
    }

    // Run the game
    engine.run();

    return 0;
}
