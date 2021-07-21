#ifndef LOADFROMBOARD
#define LOADFROMBOARD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"
class GameModel;
class loadFromBoard : public SetBoardStrategy{

 public:

  void loadBoard(GameModel *gm) override;
};
#endif