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
  std::vector<int> vertex;
  std::vector<int> tiles;
  std::vector<int> edges;
  std::vector<std::string> resources;
  std::vector<std::string> commands;
 public:
 // for all funcitons below, if there are no valid choice then return false
 // and n stay the same as insert, otherwise return true and modify n.
  bool chooseVertex(int& n, Board *board) override;
  bool chooseTile(int &n, Board *board) override;
  bool chooseColor(std::string &color, std::vector<std::string> v) override;
  bool chooseRoad(int &n, Board *board) override;
  bool answer(std::string &cmd) override;
  bool chooseResource(std::string &cmd) override;
  bool chooseCommand(std::string &cmd) override;
};
  
#endif