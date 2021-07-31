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
   void chooseInt(int m) override;
};
#endif