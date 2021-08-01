#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "SetBoardStrategy.h"
SetBoardStrategy::SetBoardStrategy() 
: tiles{{0, "BRICK"}, {1, "ENERGY"}, {2, "GLASS"},
        {3, "HEAT"},  {4, "WIFI"},   {5, "PARK"}},
  builders{{0, "Blue"}, {1, "Red"}, {2, "Orange"}, {3, "Yellow"}}
{}

void SetBoardStrategy::loadBoard(GameModel *gm){};