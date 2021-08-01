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
  bool chooseVertex(int& n) override;
  bool chooseTile(int &n) override;
  bool choosePlayer(int &n) override;
};
#endif