#include "../../Headers/Core/GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : player(nullptr),
                           quit(false),
                           ingame(false),
                           end(false),
                           onemenu(true),
                           onelevel(true),
                           playerDying(false),
                           playerWinning(false),
                           playSound(true),
                           sfxEnabled(true),
                           isPaused(false),
                           countmenu(1),
                           options(1),
                           level(0),
                           mouseClicked(false),
                           menuTexture(nullptr),
                           gameMusic(nullptr),
                           menuSelect(nullptr),
                           menuChoose(nullptr),
                           lastTime(0),
                           stateChangeTime(0)
{
    // Initialize key states array
    memset(keyStates, false, sizeof(keyStates));

    // Initialize texture arrays
    for (int i = 0; i < 3; i++)
    {
        introTexture[i] = nullptr;
        pauseTexture[i] = nullptr;
        quitTexture[i] = nullptr;
    }

    for (int i = 0; i < 5; i++)
    {
        healthTexture[i] = nullptr;
    }

    for (int i = 0; i < 4; i++)
    {
        levelTexture[i] = nullptr;
        settingTexture[i] = nullptr;
    }
}

GameEngine::~GameEngine() {}

bool GameEngine::initialize()
{
    // Initialize graphics system
    graphics.init();

    // Create cursor
    cursor.createCursor(graphics);

    // Initialize sound system
    if (!soundSystem.init(44100, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        std::cout << "Error: Failed to initialize audio system!" << std::endl;
        return false;
    }

    // Load game music
    gameMusic = soundSystem.loadMusic("Assets\\Sound\\Massah.mp3");
    if (gameMusic == nullptr)
    {
        std::cout << "Error: Failed to load music file" << std::endl;
        return false;
    }
    else
    {
        soundSystem.playMusic(gameMusic, -1);
        soundSystem.setMusicVolume(68);
    }

    // Load sound effects
    menuSelect = soundSystem.loadSound("Assets\\Sound\\sfx\\menuselect.wav");
    menuChoose = soundSystem.loadSound("Assets\\Sound\\sfx\\menuchoose.wav");

    // Load textures
    menuTexture = graphics.loadTexture("Assets\\Menu\\Menu 1.png");

    // Initialize intro textures
    for (int i = 0; i < 3; i++)
    {
        std::string path = "Assets\\Intro\\intro " + std::to_string(i + 1) + ".png";
        introTexture[i] = graphics.loadTexture(path.c_str());
    }

    // Initialize health textures
    for (int i = 0; i < 5; i++)
    {
        std::string path = "Assets\\Things\\Health\\health " + std::to_string(i + 1) + ".png";
        healthTexture[i] = graphics.loadTexture(path.c_str());
    }

    // Initialize level textures
    levelTexture[0] = graphics.loadTexture("Assets\\Menu\\level.png");
    for (int i = 0; i < 3; i++)
    {
        std::string path = "Assets\\Menu\\level " + std::to_string(i + 1) + ".png";
        levelTexture[i + 1] = graphics.loadTexture(path.c_str());
    }

    // Initialize setting textures
    for (int i = 0; i < 4; i++)
    {
        std::string path = "Assets\\Menu\\setting " + std::to_string(i + 1) + ".png";
        settingTexture[i] = graphics.loadTexture(path.c_str());
    }

    // Initialize quit textures
    for (int i = 0; i < 3; i++)
    {
        std::string path = "Assets\\Menu\\quit " + std::to_string(i + 1) + ".png";
        quitTexture[i] = graphics.loadTexture(path.c_str());
    }

    // Initialize pause menu textures
    for (int i = 0; i < 3; i++)
    {
        std::string path = "Assets\\Things\\Pause\\pause" + std::to_string(i + 1) + ".png";
        pauseTexture[i] = graphics.loadTexture(path.c_str());
    }

    // Initialize player
    player = new Player(graphics.renderer);

    // Initialize timing
    lastTime = SDL_GetTicks();

    return true;
}

void GameEngine::processInput()
{
    SDL_Event e;

    // Reset trạng thái click chuột ở đầu mỗi frame
    mouseClicked = false;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        // Phát hiện click chuột
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            mouseClicked = true;
        }
        // Update cursor position when mouse moves
        else if (e.type == SDL_MOUSEMOTION)
        {
            cursor.update();
        }
        // Pressed ESC
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            if (ingame && !playerDying && !playerWinning)
            {
                isPaused = !isPaused; // Toggle trạng thái tạm dừng
                if (isPaused)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    playSound = true; // Reset trạng thái âm thanh cho menu
                }
            }
        }
    }
}

void GameEngine::handleIntro()
{
    intro(graphics);
}

void GameEngine::handleMenu()
{
    if (onemenu)
    {
        cursor.in = 0;
        countmenu = 1;
        playSound = true;
        ingame = false;
        level = 0;
        onemenu = false;
    }

    SDL_RenderClear(graphics.renderer);

    if (!end)
    {

        menu(menuTexture, graphics, cursor, mouseClicked, countmenu, quit, playSound,
             ingame, options, level, menuSelect, menuChoose, sfxEnabled, gameMusic);

        mouseClicked = false;
    }

    cursor.draw(graphics); // Draw cursor last

    if (ingame)
    {
        SDL_RenderClear(graphics.renderer);
    }

    graphics.presentScene();
}

void GameEngine::handleGameplay()
{
    // Initialize player when entering a level
    if (onelevel)
    {
        if (level == 0 || player->health <= 0 || playerWinning)
        {
            player->health = 5;
        }

        player->width = 64;
        player->height = 64;
        player->rect = {static_cast<int>(player->x), static_cast<int>(player->y),
                        player->width, player->height};
        player->character = graphics.loadTexture("Assets/chibi/idle/idle.png");
    }

    if (!playerDying && !playerWinning)
    {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        player->handleInput(currentKeyStates, deltaTime, level);
    }
    else
    {
        // Handle player dying
        if (playerDying && SDL_GetTicks() - stateChangeTime > 500)
        {
            death(graphics, *player, menuTexture, onelevel);
            playerDying = false;

            if (player->health <= 0)
            {
                gameover(graphics, menuTexture, *player, ingame);
                onemenu = true;
            }
        }

        // Handle player winning
        if (playerWinning && SDL_GetTicks() - stateChangeTime > 500)
        {
            win(graphics, *player);
            complete(graphics, menuTexture, *player, ingame);
            playerWinning = false;
            player->health = 5;
            level = 0;
            onelevel = true;
        }
    }

    SDL_RenderClear(graphics.renderer);

    // Render the appropriate level
    if (level == 1)
    {
        level1(onelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }
    else if (level == 2)
    {
        level2(onelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }
    else if (level == 3)
    {
        level3(onelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }

    // Draw health indicators
    drawhealth(graphics, *player, menuTexture);

    graphics.presentScene();
}

void GameEngine::handleWin()
{
    win(graphics, *player);
    complete(graphics, menuTexture, *player, ingame);
    playerWinning = false;
    player->health = 5;
    level = 0;
    onelevel = true;
}

void GameEngine::handleDeath()
{
    // Đảm bảo nhân vật dừng di chuyển hoàn toàn khi chết
    player->velocityX = 0;
    player->velocityY = 0;

    death(graphics, *player, menuTexture, onelevel);
    playerDying = false;

    if (player->health <= 0)
    {
        gameover(graphics, menuTexture, *player, ingame);
        onemenu = true;
    }
}

void GameEngine::handlePauseMenu()
{
    // Biến đếm để quản lý trạng thái menu tạm dừng
    static int pauseMenuState = 1;
    bool userAction = false;   // Biến để theo dõi hành động của người dùng
    bool tempOnelevel = false; // Biến tạm cho tham số onelevel
    bool wasInGame = ingame;   // Ghi nhớ trạng thái game trước khi có thay đổi

    // Vẽ menu tạm dừng
    SDL_RenderClear(graphics.renderer);

    // Vẽ lại màn chơi hiện tại
    if (level == 1)
    {
        level1(tempOnelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }
    else if (level == 2)
    {
        level2(tempOnelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }
    else if (level == 3)
    {
        level3(tempOnelevel, graphics, *player, menuTexture, level, playerDying,
               playerWinning, stateChangeTime);
    }

    // Vẽ overlay menu tạm dừng
    pauseMenu(menuTexture, graphics, cursor, mouseClicked, pauseMenuState, userAction, playSound, ingame,
              onemenu, onelevel, options, menuSelect, menuChoose, sfxEnabled);

    // Vẽ con trỏ chuột
    cursor.draw(graphics);

    // Hiển thị cảnh
    graphics.presentScene();

    // Reset click chuột
    mouseClicked = false;

    // Chỉ tắt menu tạm dừng nếu người dùng đã thực hiện hành động (nhấn nút Resume hoặc Return)
    if (userAction)
    {
        isPaused = false;
        pauseMenuState = 1;

        // Nếu người chơi đã thoát về menu chính (ingame từ true thành false)
        if (wasInGame && !ingame)
        {
            // Đặt lại máu về 5 khi thoát về menu chính
            player->health = 5;
        }
    }
}

void GameEngine::run()
{
    // Handle intro state
    // handleIntro();

    while (!quit)
    {
        // Process input
        processInput();

        if (!ingame)
        {
            // Handle menu state
            handleMenu();
        }
        else
        {
            // Kiểm tra nếu game đang tạm dừng
            if (isPaused)
            {
                // Xử lý menu tạm dừng
                handlePauseMenu();
            }
            else
            {
                // Handle gameplay state
                handleGameplay();
            }
        }

        // Limit frame rate
        SDL_Delay(16); // ~60 FPS
    }
}

void GameEngine::cleanup()
{
    // Free player
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }

    // Free textures
    if (menuTexture != nullptr)
    {
        SDL_DestroyTexture(menuTexture);
        menuTexture = nullptr;
    }

    for (int i = 0; i < 3; i++)
    {
        if (introTexture[i] != nullptr)
        {
            SDL_DestroyTexture(introTexture[i]);
            introTexture[i] = nullptr;
        }

        if (pauseTexture[i] != nullptr)
        {
            SDL_DestroyTexture(pauseTexture[i]);
            pauseTexture[i] = nullptr;
        }

        if (quitTexture[i] != nullptr)
        {
            SDL_DestroyTexture(quitTexture[i]);
            quitTexture[i] = nullptr;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (healthTexture[i] != nullptr)
        {
            SDL_DestroyTexture(healthTexture[i]);
            healthTexture[i] = nullptr;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (levelTexture[i] != nullptr)
        {
            SDL_DestroyTexture(levelTexture[i]);
            levelTexture[i] = nullptr;
        }
        if (settingTexture[i] != nullptr)
        {
            SDL_DestroyTexture(settingTexture[i]);
            settingTexture[i] = nullptr;
        }
    }

    // Free music and sound effects
    if (gameMusic != nullptr)
    {
        Mix_FreeMusic(gameMusic);
        gameMusic = nullptr;
    }

    if (menuSelect != nullptr)
    {
        Mix_FreeChunk(menuSelect);
        menuSelect = nullptr;
    }

    if (menuChoose != nullptr)
    {
        Mix_FreeChunk(menuChoose);
        menuChoose = nullptr;
    }

    // Close sound system
    soundSystem.close();

    // Close graphics system
    graphics.quit();

    // Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}