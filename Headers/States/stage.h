#ifndef _STAGE__H
#define _STAGE__H

#include "../../src/include/SDL2/SDL.h"
#include "../States/game.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "../Entities/obstacle.h"
#include "../Entities/player.h"
using namespace std;

void level1(bool &onelevel, Graphics &graphics, Player &player,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);
void level2(bool &onelevel, Graphics &graphics, Player &player,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);
void level3(bool &onelevel, Graphics &graphics, Player &player,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);

#endif