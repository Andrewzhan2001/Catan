#ifndef COMPUTERPLAYER
#define COMPUTERPLAYER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Player.h"

class computerPlayer : public Player{
  std::vector<int> vertexnum;
  std::vector<int> Tilenum;
  std::vector<int> Player;
 public:
  computerPlayer();
  bool chooseVertex(int& n) override;
  bool chooseTile(int &n) override;
  bool choosePlayer(int &n) override;
};
#endif