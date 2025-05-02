#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <bits/stdc++.h>
#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../../src/include/SDL2/SDL_mixer.h"
#include "../Systems/defs.h"
#include "graphics.h"
#include "../Systems/cursor.h"
#include "../Entities/player.h"
#include "../Systems/animation.h"
#include "../States/game.h"
#include "../Entities/obstacle.h"
#include "../Entities/stage.h"
#include "../Systems/sound.h"

/**
 * @class GameEngine
 * @brief Main game controller that manages all game systems
 */
class GameEngine
{
private:
    // Core components
    Graphics graphics;
    Cursor cursor;
    Player *player;

    // Game state
    bool quit;
    bool ingame;
    bool end;
    bool onemenu;
    bool onelevel;
    bool playerDying;
    bool playerWinning;
    bool playSound;
    bool sfxEnabled;
    bool isPaused; // Thêm biến theo dõi trạng thái tạm dừng

    // Menu and level state
    int countmenu;
    int options;
    int level;

    // Mouse state tracking
    bool mouseClicked; // Thêm biến để theo dõi trạng thái chuột

    // Resources
    SDL_Texture *menuTexture;
    SDL_Texture *introTexture[3];
    SDL_Texture *healthTexture[5];
    SDL_Texture *levelTexture[4];
    SDL_Texture *settingTexture[4];
    SDL_Texture *quitTexture[3];
    SDL_Texture *pauseTexture[3];

    Mix_Music *gameMusic;
    Mix_Chunk *menuSelect;
    Mix_Chunk *menuChoose;

    // Timing variables
    Uint32 lastTime;
    Uint32 stateChangeTime;

    // Key states
    bool keyStates[SDL_NUM_SCANCODES];

    /**
     * @brief Initializes all game components
     */
    bool initializeComponents();

    void handleIntro();

    void handleMenu();

    void handleGameplay();

    void handlePauseMenu();

    void handleWin();

    void handleDeath();

    /**
     * @brief Processes user input each frame
     */
    void processInput();

public:
    /**
     * @brief Constructor for GameEngine
     */
    GameEngine();

    /**
     * @brief Destructor for GameEngine
     */
    ~GameEngine();

    /**
     * @brief Initializes the game engine
     */
    bool initialize();

    /**
     * @brief Runs the main game loop
     */
    void run();

    /**
     * @brief Cleans up resources before exit
     */
    void cleanup();

    bool wasMouseClicked() { return mouseClicked; }

    void resetMouseClick() { mouseClicked = false; }
};

#endif // GAME_ENGINE_H