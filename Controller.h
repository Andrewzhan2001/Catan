#ifndef CONTROLLER
#define CONTROLLER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "GameModel.h"

class SetBoardStrategy;
class Controller{
  std::unique_ptr<GameModel> gm;
  size_t seed = 0;
 public:
  Controller();
  void setseed(size_t seed); // set the seed for random value;
  void loadStrategy(SetBoardStrategy *sbs); // use stategy sbs to load the board
  void saveFile(std::string fname = "backup.sv");
  bool play();// start the game
  
  // for debug
  void print();
};
#endif