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
  bool chooseBasement(int& n, Board *board) override;
  bool chooseTile(int &n, Board *board) override;
  bool chooseColor(std::string &cmd, std::vector<std::string> v) override;
  bool chooseRoadToBuild(Board *board) override;
  bool chooseBasementToBuild(Board *board) override;
  bool answer(std::string &cmd) override;
  bool chooseResource(std::string &cmd) override;
  bool chooseCommand(std::string &cmd) override;
};
#endif