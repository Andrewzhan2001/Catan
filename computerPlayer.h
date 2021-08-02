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
  bool chooseVertex(int& n, Board *board) override;
  bool chooseTile(int &n, Board *board) override;
  bool chooseColor(std::string &cmd, std::vector<std::string> v) override;
  bool chooseRoad(int &n, Board *board) override;
  bool answer(std::string &cmd) override;
  bool chooseResource(std::string &cmd) override;
  bool chooseCommand(std::string &cmd) override;
};
  
#endif