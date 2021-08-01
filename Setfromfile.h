#ifndef SETFROMFILE
#define SETFROMFILE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"

class GameModel;
class Setfromfile : public SetBoardStrategy {
  std::string file;
 public:
  Setfromfile(std::string file);
  void loadBoard(GameModel *bm) override;
};
#endif