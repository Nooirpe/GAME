#ifndef _STAGE__H
#define _STAGE__H

#include "../../src/include/SDL2/SDL.h"
#include "../States/game.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "obstacle.h"
#include "player.h"
using namespace std;

/**
 * @brief Handles gameplay for level 1
 */
void level1(bool &onelevel, Graphics &graphics, Player &player, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);

/**
 * @brief Handles gameplay for level 2
 */
void level2(bool &onelevel, Graphics &graphics, Player &player, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);

/**
 * @brief Handles gameplay for level 3
 */
void level3(bool &onelevel, Graphics &graphics, Player &player, int &level,
            bool &playerDying, bool &playerWinning, Uint32 &stateChangeTime);

#endif