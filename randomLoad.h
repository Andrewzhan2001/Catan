#ifndef RANDOMLOAD
#define RANDOMLOAD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"

class GameModel;

class randomLoad : public SetBoardStrategy{

 public:
  bool loadBoard(GameModel *bm) override;
};
#endif