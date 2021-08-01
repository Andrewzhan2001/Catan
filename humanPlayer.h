#ifndef HUMANPLAYER
#define HUMANPLAYER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Player.h"

class humanPlayer : public Player{

 public:
   bool chooseInt(int& n) override;
};
#endif