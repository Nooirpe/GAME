#ifndef _GAME__H
#define _GAME__H
#include "../Entities/player.h"
#include "../../src/include/SDL2/SDL.h"
#include "../../src/include/SDL2/SDL_image.h"
#include "../Core/graphics.h"
#include "../Systems/cursor.h"
#include "../Systems/sound.h"
#include <bits/stdc++.h>

using namespace std;

void intro(Graphics graphics);

void AudioSettings(int options, bool &sfxEnabled);

void menu(Graphics &graphics, Cursor &cursor, bool mouseClicked, int &count, bool &quit, bool &playSound, bool &ingame, int &options, int &level, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose, bool &sfxEnabled);

void pauseMenu(Graphics &graphics, Cursor &cursor, bool mouseClicked, int &count, bool &userAction, bool &playSound, bool &ingame, bool &oneMenu, bool &oneLevel, Mix_Chunk *menuSelect, Mix_Chunk *menuChoose, bool &sfxEnabled);

void drawhealth(Graphics &graphics, Player &player);

void win(Graphics &graphics);

void death(Graphics &graphics, Player &player, SDL_Texture *mn, bool &onelevel);

void gameover(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame);

void complete(Graphics &graphics, SDL_Texture *&mn, Player &player, bool &ingame);

#endif