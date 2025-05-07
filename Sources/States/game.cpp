#include "../../Headers/States/game.h"
#include "../../Headers/Entities/player.h"
#include "../../Headers/Core/graphics.h"
#include "../../Headers/Entities/obstacle.h"
#include "../../Headers/States/stage.h"
#include "../../Headers/Systems/sound.h"

void intro(Graphics graphics)
{
    SDL_Texture *show = graphics.loadTexture("Assets\\Intro\\Intro 1.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(2780);

    SDL_DestroyTexture(show);
    show = graphics.loadTexture("Assets\\Intro\\Intro 2.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(2780);

    SDL_DestroyTexture(show);
    show = graphics.loadTexture("Assets\\Intro\\Intro 3.png");
    graphics.prepareScene(show);
    graphics.presentScene();

    SDL_Delay(700);
    SDL_DestroyTexture(show);
}

void AudioSettings(int options, bool &sfxEnabled)
{
    soundSystem.applyAudioSettings(options, sfxEnabled);
}

void menu(Graphics &graphics, Cursor &cursor, bool mouseClicked, int &count, bool &quit, bool &playSound, bool &ingame, int &options, int &level, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose, bool &sfxEnabled)
{
    cursor.update();
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    SDL_Texture *tempTexture = nullptr;

    // Xử lý phím ESC
    if (currentKeyStates[SDL_SCANCODE_ESCAPE] && (count == 2 || count == 3 || count == 4))
    {
        soundSystem.playSound(menuSelect, sfxEnabled);
        count = 1;
    }

    // Xử lý menu dựa trên vị trí chuột và trạng thái click
    if (count == 1)
    {
        if (cursor.point.x > 541 && cursor.point.x < 877)
        {
            if (cursor.point.y > 361 && cursor.point.y < 474)
            {
                cursor.in = 1;
                tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 2.png");
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }

                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    count = 2;
                }
            }
            else if (cursor.point.y > 511 && cursor.point.y < 630)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 3.png");
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    count = 3;
                }
            }
            else if (cursor.point.y > 653 && cursor.point.y < 743)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 4.png");
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    count = 4;
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
                tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 1.png");
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
            tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 1.png");
        }
    }
    else if (count == 2)
    {
        if (cursor.point.y > 280 && cursor.point.y < 604)
        {
            if (cursor.point.x > 176 && cursor.point.x < 399)
            {
                cursor.in = 1;
                tempTexture = graphics.loadTexture("Assets\\Menu\\level 1.png");
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    for (int i = 0; i < 12; i++)
                    {
                        if (tempTexture)
                        {
                            SDL_DestroyTexture(tempTexture);
                        }
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(tempTexture);
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level 1.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }

                    if (tempTexture)
                    {
                        SDL_DestroyTexture(tempTexture);
                    }
                    tempTexture = nullptr;

                    ingame = 1;
                    level = 1;
                    return;
                }
            }
            else if (cursor.point.x > 574 && cursor.point.x < 829)
            {
                cursor.in = 1;
                tempTexture = graphics.loadTexture("Assets\\Menu\\level 2.png");
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    for (int i = 0; i < 12; i++)
                    {
                        if (tempTexture)
                        {
                            SDL_DestroyTexture(tempTexture);
                        }
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(tempTexture);
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level 2.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }

                    if (tempTexture)
                    {
                        SDL_DestroyTexture(tempTexture);
                    }
                    tempTexture = nullptr;

                    ingame = 1;
                    level = 2;
                    return;
                }
            }
            else if (cursor.point.x > 974 && cursor.point.x < 1226)
            {
                cursor.in = 1;
                tempTexture = graphics.loadTexture("Assets\\Menu\\level 3.png");
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    for (int i = 0; i < 12; i++)
                    {
                        if (tempTexture)
                        {
                            SDL_DestroyTexture(tempTexture);
                        }
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);

                        SDL_DestroyTexture(tempTexture);
                        tempTexture = graphics.loadTexture("Assets\\Menu\\level 3.png");
                        graphics.prepareImg(tempTexture);
                        graphics.presentScene();
                        SDL_Delay(50);
                    }

                    if (tempTexture)
                    {
                        SDL_DestroyTexture(tempTexture);
                    }
                    tempTexture = nullptr;

                    ingame = 1;
                    level = 3;
                    return;
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
                tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");
            }
        }
        else if (cursor.point.x > 76 && cursor.point.x < 138 && cursor.point.y > 122 && cursor.point.y < 192)
        {
            cursor.in = 1;
            tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");

            if (playSound)
            {
                soundSystem.playSound(menuChoose, sfxEnabled);
                playSound = false;
            }

            if (mouseClicked)
            {
                soundSystem.playSound(menuSelect, sfxEnabled);
                count = 1;
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
            tempTexture = graphics.loadTexture("Assets\\Menu\\level.png");
        }
    }
    else if (count == 3)
    {
        if (options == 1)
        {
            tempTexture = graphics.loadTexture("Assets\\Menu\\setting 1.png");
        }
        else if (options == 3)
        {
            tempTexture = graphics.loadTexture("Assets\\Menu\\setting 3.png");
            options = 3;
        }
        else if (options == 5)
        {
            tempTexture = graphics.loadTexture("Assets\\Menu\\setting 4.png");
            options = 5;
        }
        else if (options == 6)
        {
            tempTexture = graphics.loadTexture("Assets\\Menu\\setting 2.png");
        }
        if (cursor.point.x > 790 && cursor.point.x < 826)
        {
            if (cursor.point.y > 438 && cursor.point.y < 475)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (mouseClicked)
                {
                    if (options == 1)
                    {
                        options = 3;
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 3)
                    {
                        options = 1;
                        soundSystem.playSound(menuSelect, sfxEnabled);
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 6)
                    {
                        options = 5;
                        soundSystem.playSound(menuSelect, sfxEnabled);
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 5)
                    {
                        options = 6;
                        AudioSettings(options, sfxEnabled);
                    }
                }
            }
            else if (cursor.point.y > 516 && cursor.point.y < 551)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                if (mouseClicked)
                {
                    if (options == 1)
                    {
                        options = 5;
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 5)
                    {
                        options = 1;
                        soundSystem.playSound(menuSelect, sfxEnabled);
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 6)
                    {
                        options = 3;
                        soundSystem.playSound(menuSelect, sfxEnabled);
                        AudioSettings(options, sfxEnabled);
                    }
                    else if (options == 3)
                    {
                        options = 6;
                        AudioSettings(options, sfxEnabled);
                    }
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
            }
        }
        else if (cursor.point.x > 390 && cursor.point.x < 440 && cursor.point.y > 339 && cursor.point.y < 371)
        {
            cursor.in = 1;
            if (playSound)
            {
                soundSystem.playSound(menuChoose, sfxEnabled);
                playSound = false;
            }
            if (mouseClicked)
            {
                soundSystem.playSound(menuSelect, sfxEnabled);
                count = 1;
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
        }
    }
    else if (count == 4)
    {
        if (cursor.point.y > 539 && cursor.point.y < 584)
        {
            if (cursor.point.x > 541 && cursor.point.x < 633)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                tempTexture = graphics.loadTexture("Assets\\Menu\\quit 2.png");

                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    if (tempTexture)
                    {
                        SDL_DestroyTexture(tempTexture);
                        tempTexture = nullptr;
                    }
                    quit = true;
                    return;
                }
            }
            else if (cursor.point.x > 806 && cursor.point.x < 900)
            {
                cursor.in = 1;
                if (playSound)
                {
                    soundSystem.playSound(menuChoose, sfxEnabled);
                    playSound = false;
                }
                tempTexture = graphics.loadTexture("Assets\\Menu\\quit 3.png");
                if (mouseClicked)
                {
                    soundSystem.playSound(menuSelect, sfxEnabled);
                    count = 1;
                }
            }
            else
            {
                cursor.in = 0;
                playSound = true;
                tempTexture = graphics.loadTexture("Assets\\Menu\\quit 1.png");
            }
        }
        else
        {
            cursor.in = 0;
            playSound = true;
            tempTexture = graphics.loadTexture("Assets\\Menu\\quit 1.png");
        }
    }

    if (tempTexture)
    {
        graphics.prepareImg(tempTexture);
        SDL_DestroyTexture(tempTexture);
    }
}
void drawhealth(Graphics &graphics, Player &player)
{
    SDL_Texture *healthTexture = nullptr;
    if (player.health == 5)
    {
        healthTexture = graphics.loadTexture("Assets\\Things\\Health\\health 5.png");
    }
    else if (player.health == 4)
    {
        healthTexture = graphics.loadTexture("Assets\\Things\\Health\\health 4.png");
    }
    else if (player.health == 3)
    {
        healthTexture = graphics.loadTexture("Assets\\Things\\Health\\health 3.png");
    }
    else if (player.health == 2)
    {
        healthTexture = graphics.loadTexture("Assets\\Things\\Health\\health 2.png");
    }
    else if (player.health == 1)
    {
        healthTexture = graphics.loadTexture("Assets\\Things\\Health\\health 1.png");
    }

    if (healthTexture)
    {
        // render
        SDL_RenderCopy(graphics.renderer, healthTexture, NULL, NULL);
        SDL_DestroyTexture(healthTexture);
    }
}

void pauseMenu(Graphics &graphics, Cursor &cursor, bool mouseClicked, int &count, bool &userAction, bool &playSound, bool &ingame, bool &oneMenu, bool &oneLevel, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose, bool &sfxEnabled)
{
    cursor.update();
    SDL_Texture *tempTexture = nullptr;

    // Đặt giá trị mặc định là false - người dùng chưa thực hiện hành động
    userAction = false;

    tempTexture = graphics.loadTexture("Assets\\Things\\Pause\\pause1.png");
    cursor.in = 0;

    if (cursor.point.x > 460 && cursor.point.x < 845 && cursor.point.y > 310 && cursor.point.y < 375)
    {
        cursor.in = 1;
        SDL_DestroyTexture(tempTexture);
        tempTexture = graphics.loadTexture("Assets\\Things\\Pause\\pause2.png");

        // Play sound effect if just started hovering
        if (playSound)
        {
            soundSystem.playSound(menuChoose, sfxEnabled);
            playSound = false;
        }

        // Check for mouse click to resume game
        if (mouseClicked)
        {
            soundSystem.playSound(menuSelect, sfxEnabled);
            userAction = true; // Người dùng đã nhấp vào nút Resume
            if (tempTexture)
            {
                SDL_DestroyTexture(tempTexture);
                tempTexture = nullptr;
            }
            return;
        }
    }
    else if (cursor.point.x > 460 && cursor.point.x < 845 && cursor.point.y > 440 && cursor.point.y < 503)
    {
        SDL_DestroyTexture(tempTexture);
        tempTexture = graphics.loadTexture("Assets\\Things\\Pause\\pause3.png");

        // Play sound effect if just started hovering
        if (playSound)
        {
            soundSystem.playSound(menuChoose, sfxEnabled);
            playSound = false;
        }

        // Check for mouse click to return to main menu
        if (mouseClicked)
        {
            soundSystem.playSound(menuSelect, sfxEnabled);
            userAction = true; // Người dùng đã nhấp vào nút Return to Menu

            // Return to main menu
            if (tempTexture)
            {
                SDL_DestroyTexture(tempTexture);
                tempTexture = nullptr;
            }

            // Clean up and transition to menu
            SDL_RenderClear(graphics.renderer);
            graphics.presentScene();

            ingame = false;  // Exit game mode
            oneMenu = true;  // Enable menu
            oneLevel = true; // Reset level
            count = 1;       // Set menu to first screen

            // Load menu
            tempTexture = graphics.loadTexture("Assets\\Menu\\Menu 1.png");
            graphics.prepareImg(tempTexture);
            graphics.presentScene();
            SDL_DestroyTexture(tempTexture);

            return;
        }
    }
    else
    {
        cursor.in = 0;
        // Reset sound flag when not hovering over any button
        playSound = true;
    }

    // Render the current menu texture
    if (tempTexture)
    {
        graphics.prepareImg(tempTexture);
        SDL_DestroyTexture(tempTexture);
    }
}

void win(Graphics &graphics)
{
    SDL_Texture *mn = graphics.loadTexture("Assets\\Things\\win.png");
    SDL_RenderClear(graphics.renderer);
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(2000);
    SDL_DestroyTexture(mn);
}

void death(Graphics &graphics, Player &player, SDL_Texture *mn, bool &onelevel)
{
    SDL_RenderClear(graphics.renderer);
    player.health--;
    if (player.health == 4)
    {
        mn = graphics.loadTexture("Assets\\Things\\Death\\5.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("Assets\\Things\\Death\\4.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 3)
    {
        mn = graphics.loadTexture("Assets\\Things\\Death\\4.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("Assets\\Things\\Death\\3.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 2)
    {
        mn = graphics.loadTexture("Assets\\Things\\Death\\3.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("Assets\\Things\\Death\\2.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 1)
    {
        mn = graphics.loadTexture("Assets\\Things\\Death\\2.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("Assets\\Things\\Death\\1.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    else if (player.health == 0)
    {
        mn = graphics.loadTexture("Assets\\Things\\Death\\1.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1200);
        SDL_DestroyTexture(mn);
        mn = graphics.loadTexture("Assets\\Things\\Death\\0.png");
        graphics.prepareImg(mn);
        graphics.presentScene();
        SDL_Delay(1500);
        onelevel = 1;
    }
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
}
void gameover(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame)
{
    SDL_DestroyTexture(mn);
    SDL_RenderClear(graphics.renderer);
    mn = graphics.loadTexture("Assets\\Things\\gameover.png");
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(1200);
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
    player.health = 5;
    ingame = 0;
}
void complete(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame)
{
    SDL_DestroyTexture(mn);
    SDL_RenderClear(graphics.renderer);
    mn = graphics.loadTexture("Assets\\Things\\complete.png");
    graphics.prepareImg(mn);
    graphics.presentScene();
    SDL_Delay(2000);
    SDL_RenderClear(graphics.renderer);
    graphics.presentScene();
    SDL_Delay(1000);
    SDL_DestroyTexture(mn);
    player.health = 5;
    ingame = 0;
}
