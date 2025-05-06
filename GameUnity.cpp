#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// SDL files
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"

// Source files for the unity build
// Core
#include "Sources/Core/graphics.cpp"
#include "Sources/Core/GameEngine.cpp"

// Systems
#include "Sources/Systems/animation.cpp"
#include "Sources/Systems/cursor.cpp"
#include "Sources/Systems/sound.cpp"

// Entities
#include "Sources/Entities/player.cpp"
#include "Sources/Entities/obstacle.cpp"

// States
#include "Sources/States/game.cpp"
#include "Sources/States/stage.cpp"
