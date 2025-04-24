#ifndef _STAGE__H
#define _STAGE__H

#include <C:\C++\GAME\GAME\src\include\SDL2\SDL.h>
#include "game.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "obstacle.h"
#include "player.h"
using namespace std;

void level1(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);
void level2(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);
void level3(bool &onelevel, Graphics &graphics, Player &player, SDL_Texture *&mn, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);

#endif